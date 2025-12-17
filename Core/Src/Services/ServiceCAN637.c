// serviceCan637:
// Historique: 
// 2025-12-01, cr�ation � partir de serviceProtocole637 pour utilisation via CAN1
// 2025-12-xx, mise au propre et ajustement avec piloteCAN1 multi-ID

// INCLUSIONS
#include "main.h"
#include "pilote_CAN.h"
#include "serviceBaseTemps.h"
#include "ServiceCAN637.h"

// D�clarations de fonctions priv�es
void serviceCan637_gereLaTransmission(void);
void serviceCan637_gereLaReception(void);

// Variable externe : header CAN rempli par piloteCAN1_litUnMessageRecu()
extern CAN_RxHeaderTypeDef piloteCAN1_reception;

// D�finition de la variable publique
SERVICECAN637 serviceCan637;

// ---------------------------------------------------------------------
//                     GESTION DE LA TRANSMISSION
// ---------------------------------------------------------------------
void serviceCan637_gereLaTransmission(void)
{
  // Aucune requ�te en attente ?
  if (serviceCan637.requete == REQUETE_TRAITEE)
  {
    return;
  }

  // Validation de la longueur demand�e
  if (serviceCan637.nombreATransmettre == 0)
  {
    serviceCan637.statut  = SERVICECAN637_ERREUR_LONGUEUR_NULLE;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  if (serviceCan637.nombreATransmettre > SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM)
  {
    serviceCan637.statut  = SERVICECAN637_ERREUR_LONGUEUR_TROP_GRANDE;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  // Si aucune mailbox CAN n'est libre, on r�essaiera au prochain tick
  if (piloteCAN1_messageTransmis() == 0)
  {
    // On laisse la requ�te ACTIVE, on retentera plus tard
    return;
  }

  // Transmission CAN via le pilote
  // L'ID utilis� vient de main.h : PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION
  if (piloteCAN1_transmetDesDonnes(serviceCan637.idATransmettre,
                                   serviceCan637.octetsATransmettre,
                                   serviceCan637.nombreATransmettre)
      != PILOTECAN1_TRANSMIS)
  {
    serviceCan637.statut  = SERVICECAN637_ERREUR_TRANSMISSION;
    serviceCan637.requete = REQUETE_TRAITEE;
    return;
  }

  // Tout s'est bien pass�
  serviceCan637.statut  = SERVICECAN637_PAS_D_ERREURS;
  serviceCan637.requete = REQUETE_TRAITEE;
}

// ---------------------------------------------------------------------
//                     GESTION DE LA R�CEPTION
// ---------------------------------------------------------------------
 void serviceCan637_gereLaReception(void)
{
  unsigned char tampon[8];  // tampon brut, 8 max en CAN
  unsigned char i;

  // Si l'information pr�c�dente n'a pas encore �t� lue par l'interface,
  // on ne remplace pas le buffer pour �viter d'�craser des donn�es.
  if (serviceCan637.information == INFORMATION_DISPONIBLE)
  {
    return;
  }

  // Est-ce qu'il y a au moins une trame dans le FIFO CAN ?
  if (piloteCAN1_messageDisponible() == 0)
  {
    return;
  }

  // On lit UNE trame via le pilote de base
  if (piloteCAN1_litUnMessageRecu(tampon) != PILOTECAN1_DISPONIBLE)
  {
    // Erreur ou aucune trame avec ID accept�
    serviceCan637.nombreARecevoir = 0;
    serviceCan637.statut          = SERVICECAN637_ERREUR_RECEPTION;
    serviceCan637.information     = INFORMATION_DISPONIBLE; // signale une info d'erreur
    return;
  }

  // Le nombre d'octets re�us est dans le header CAN (DLC)
  serviceCan637.nombreARecevoir = piloteCAN1_reception.DLC;

  // S�curit� : limiter au buffer maximum du service
  if (serviceCan637.nombreARecevoir > SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM)
  {
    serviceCan637.nombreARecevoir = SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM;
  }

  // Copie dans le buffer public
  for (i = 0; i < serviceCan637.nombreARecevoir; i++)
  {
    serviceCan637.octetsRecus[i] = tampon[i];
  }

  // Zero du reste du buffer pour �tre propre
  for (; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
  {
    serviceCan637.octetsRecus[i] = 0;
  }

  serviceCan637.statut      = SERVICECAN637_PAS_D_ERREURS;
  serviceCan637.information = INFORMATION_DISPONIBLE;
}

// ---------------------------------------------------------------------
//                     INITIALISATION DU SERVICE CAN637
// ---------------------------------------------------------------------
void serviceCan637_initialise(void)
{
  unsigned char i;
  serviceCan637.idATransmettre = CAN_ID_ARRET;
  serviceCan637.etatDuModuleDeReception = MODULE_PAS_EN_FONCTION;
  serviceCan637.information             = INFORMATION_TRAITEE;
  serviceCan637.requete                 = REQUETE_TRAITEE;
  serviceCan637.nombreATransmettre      = 0;
  serviceCan637.nombreARecevoir         = 0;
  serviceCan637.statut                  = SERVICECAN637_PAS_D_ERREURS;

  for (i = 0; i < SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM; i++)
  {
    serviceCan637.octetsATransmettre[i] = 0;
    serviceCan637.octetsRecus[i]        = 0;
  }

  // Enregistrement des fonctions dans le service de base de temps
  serviceBaseDeTemps_execute[TRANSMISSION_CAN_PHASE] =
      serviceCan637_gereLaTransmission;

  serviceBaseDeTemps_execute[RECEPTION_CAN_PHASE] =
      serviceCan637_gereLaReception;

  serviceCan637.etatDuModuleDeReception = MODULE_EN_FONCTION;
}
