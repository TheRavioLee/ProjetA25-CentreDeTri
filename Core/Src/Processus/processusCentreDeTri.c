/*
 * processusCentreDeTri.c
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_Timers.h"
#include "ServiceBaseTemps.h"
#include "interface_PCF8574.h"
#include "interface_BoutonBleu.h"
#include "processusEntreesNumeriques.h"
#include "processusEntreeAnalogique.h"
#include "processusSortiesNumeriques.h"

//Definitions privees
#define BOUTON_BLEU interfaceBtnBleu.etatBouton
#define INFO_BTN_BLEU interfaceBtnBleu.information

#define TEMPS_MAXIMUM 250 // 250 * 9ms = ~2.5s

uint8_t modeCentreTri;

//Fonctions privees
void processusCentreModeAttente(void);
void processusCentreModeTest(void);

void processusCentreTestEntrees(void);
void processusCentreTestVerinMagasin(void);
void processusCentreTestElevateur(void);
void processusCentreTestConvoyeur(void);
void processusCentreTestEjecteur(void);
void processusCentreTestVentouseVaccum(void);
void processusCentreTestVentouseHauteur(void);

void processusCentreModeOperation(void);
void processusCentreModeArret(void);
void processusCentreModeErreur(void);

void processusCentreModeAttente(void)
{
	modeCentreTri = ATTENTE;
	//faire lecture des entrees pour assurer aucune erreur
	// si erreur -> mode erreur bloquant
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x55= init
				|| (interfacePCF8574.entreesCarte2 & ~0x34) != 0) 	//0x30 = init, sauf boutons rouge/vert
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (INFO_BTN_BLEU == INFORMATION_DISPONIBLE && BOUTON_BLEU == BOUTON_APPUYE)
	{
		INFO_BTN_BLEU = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeTest;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeOperation;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreModeArret(void)
{
    static uint8_t compteurAppuye = 0;
    static uint16_t timerDoublePress = 0;

    static uint8_t etatStable = BOUTON_RELACHE;      // debounced state
    static uint8_t compteurStabilite = 0;            // debounce counter

    uint8_t etatBrut = BOUTON_VERT;                  // 0 or 1

    modeCentreTri = ARRET;
    interfacePCF8574.information = INFORMATION_TRAITEE;

    // ---- Debounce ----
    if (etatBrut != etatStable)
    {
        compteurStabilite++;
        if (compteurStabilite >= 3)   // 3 × 10ms = 30ms
        {
            etatStable = etatBrut;    // accept new stable state
            compteurStabilite = 0;
        }
    }
    else
    {
        compteurStabilite = 0;        // stable again
    }

    // ---- Rising edge detection ----
    static uint8_t ancienEtat = BOUTON_RELACHE;

    if (ancienEtat == BOUTON_RELACHE &&
        etatStable == BOUTON_APPUYE)
    {
        // RISING EDGE
        compteurAppuye++;

        if (compteurAppuye == 1)
        {
            timerDoublePress = 0;
        }
        else if (compteurAppuye == 2 && timerDoublePress < 1000)
        {
            serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
                    processusCentreModeOperation;

            compteurAppuye = 0;
            ancienEtat = etatStable;
            return;
        }
    }

    ancienEtat = etatStable;

    // ---- Double-press timeout ----
    if (compteurAppuye > 0)
    {
        timerDoublePress += 10;
        if (timerDoublePress >= 1000)
            compteurAppuye = 0;
    }
}


void processusCentreModeTest(void)
{
	modeCentreTri = TEST;
	serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
			processusCentreTestEntrees;
}

void processusCentreTestEntrees(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x55 = init
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init, sauf boutons rouge/vert
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_POUSSOIR_POS_ENTREE_SOLE719();
		SET_POUSSOIR_POS_SORTIE_SOLE722();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestVerinMagasin;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreTestVerinMagasin(void)
{
	static uint16_t compteurVerin = 0;

	compteurVerin++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x95 = init, sauf poussoir = sortie
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
		{
			compteurVerin = 0; // reset pour prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		compteurVerin = 0; // reset pour prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_POUSSOIR_POS_SORTIE_SOLE722();
		SET_POUSSOIR_POS_ENTREE_SOLE719();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (compteurVerin == TEMPS_MAXIMUM)
	{
		CLEAR_POUSSOIR_POS_SORTIE_SOLE722();
		SET_POUSSOIR_POS_ENTREE_SOLE719();
		return;
	}

	if (compteurVerin > TEMPS_MAXIMUM)
	{
		if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
		{
			compteurVerin = 0; // reset pour prochain test
			interfacePCF8574.requete = REQUETE_ACTIVE;
			SET_ELEV_HAUT_SOLE716();
			CLEAR_ELEV_BAS_SOLE713();
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreTestElevateur;
		}
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreTestElevateur(void)
{
	static uint16_t compteurElevateur = 0;

	compteurElevateur++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x75) != 0			//0x75 = init, sauf elevateur = haut
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
		{
			compteurElevateur = 0; // reset prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		compteurElevateur = 0; // reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (compteurElevateur >= TEMPS_MAXIMUM && ELEVATEUR_HAUT != 0)
	{
		compteurElevateur = 0; // reset prochain test
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_ELEV_HAUT_SOLE716();
		SET_ELEV_BAS_SOLE713();
		SET_RELAIS_MOTEUR_CONVOYEUR();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestConvoyeur;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreTestConvoyeur(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x75) != 0			//0x75 = init, convoyeur pas de sortie; suppose que temps elevateur = haut trop grand pour
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert|  detecter avant prochaine phase
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_RELAIS_MOTEUR_CONVOYEUR();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_RELAIS_MOTEUR_CONVOYEUR();
		SET_EJECT_POS_SORTIE_SOLE725();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestEjecteur;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreTestEjecteur(void)
{
	static uint16_t compteurEjecteur = 0;

	compteurEjecteur++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{		//CHANGER POUR VRAI TEST -> 0x59??
		if ((interfacePCF8574.entreesCarte1 & ~0x5D) != 0			//0x59 = init, sauf ejecteur = sortie
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
		{
			compteurEjecteur = 0; // reset prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		compteurEjecteur = 0; // reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_EJECT_POS_SORTIE_SOLE725();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (compteurEjecteur >= TEMPS_MAXIMUM && EJECT_POS_SORTIE != 0)
	{
		compteurEjecteur = 0; // reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_EJECT_POS_SORTIE_SOLE725();
		SET_VACCUM_SOLE710();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestVentouseVaccum;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreTestVentouseVaccum(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x55 = init
				|| (interfacePCF8574.entreesCarte2 & ~0x70) != 0)	//0x70 = init, sauf boutons rouge/vert et vaccum ventouse
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_VACCUM_SOLE710();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_VACCUM_SOLE710();
		SET_VENTOUSE_BAS_SOLE704();
		CLEAR_VENTOUSE_HAUT_SOLE707();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestVentouseHauteur;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreTestVentouseHauteur(void)
{
	uint16_t compteurVentouseHauteur = 0;

	compteurVentouseHauteur++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{	//CHANGER POUR VRAI TEST -> 0X56??
		if ((interfacePCF8574.entreesCarte1 & ~0x57) != 0			//0x56 = init, sauf ventouse = bas
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0)	//0x70 = init, sauf boutons rouge/vert
		{
			compteurVentouseHauteur = 0; //reset prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		compteurVentouseHauteur = 0; //reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_VENTOUSE_BAS_SOLE704();
		SET_VENTOUSE_HAUT_SOLE707();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (compteurVentouseHauteur >= TEMPS_MAXIMUM && VENTOUSE_BAS != 0)
	{
		compteurVentouseHauteur = 0; //reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_VENTOUSE_BAS_SOLE704();
		SET_VENTOUSE_HAUT_SOLE707();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeAttente;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreModeOperation(void)
{
	modeCentreTri = OPERATION;
}

void processusCentreModeErreur(void)
{
	piloteTimer14_arreteLesInterruptions();
}

void processusCentreDeTri_Init(void)
{
	//initialiser sorties
	CLEAR_LUMIERE_VERTE();
	CLEAR_VENTOUSE_BAS_SOLE704();
	SET_VENTOUSE_HAUT_SOLE707();
	CLEAR_VACCUM_SOLE710();
	SET_ELEV_BAS_SOLE713();
	CLEAR_ELEV_HAUT_SOLE716();
	SET_POUSSOIR_POS_ENTREE_SOLE719();
	CLEAR_POUSSOIR_POS_SORTIE_SOLE722();
	CLEAR_EJECT_POS_SORTIE_SOLE725();
	CLEAR_RELAIS_MOTEUR_CONVOYEUR();


	serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeAttente;
}

