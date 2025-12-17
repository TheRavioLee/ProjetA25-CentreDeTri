#ifndef SERVICECAN637_H
#define SERVICECAN637_H

//MODULE: serviceCan637
//DESCRIPTION: implémente un service de communication 247-637 via le CAN1
//             en utilisant le pilote piloteCAN1 et le service de base de temps.

//HISTORIQUE:
// 2025-12-01, adaptation à partir de serviceProtocole637 pour utilisation sur CAN

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define SERVICECAN637_PHASE_RECEPTION        0
//#define SERVICECAN637_PHASE_TRANSMISSION     1
//#define SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM  8
//
// (4 car S0008 envoie/reçoit 4 octets, tu peux mettre 8 si tu veux exploiter tout le CAN)

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define SERVICECAN637_PAS_D_ERREURS              0
#define SERVICECAN637_ERREUR_TRANSMISSION        1
#define SERVICECAN637_ERREUR_RECEPTION           2
#define SERVICECAN637_ERREUR_LONGUEUR_NULLE      3
#define SERVICECAN637_ERREUR_LONGUEUR_TROP_GRANDE 4

typedef struct
{
  unsigned char etatDuModuleDeReception;  // MODULE_EN_FONCTION / MODULE_PAS_EN_FONCTION

  unsigned char information;              // INFORMATION_TRAITEE / INFORMATION_DISPONIBLE
  unsigned char octetsRecus[SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM];

  unsigned char requete;                  // REQUETE_TRAITEE / REQUETE_ACTIVE
  unsigned char nombreATransmettre;
  unsigned char octetsATransmettre[SERVICECAN637_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned int idATransmettre;            // ID CAN à utiliser pour la prochaine trame TX
  unsigned char nombreARecevoir;
  unsigned char statut;                   // SERVICECAN637_xxx
} SERVICECAN637;

//Fonctions publiques:
void serviceCan637_initialise(void);

//Variables publiques:
extern SERVICECAN637 serviceCan637;

#endif
