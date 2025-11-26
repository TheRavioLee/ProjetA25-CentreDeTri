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

//Fonctions privees
void processusCentreModeAttente(void);
void processusCentreModeTest(void);

void processusCentreTestEntrees(void);
void processusCentreTestVerinMagasin(void);
void processusCentreTestElevateur(void);
void processusCentreTestConvoyeur(void);
void processusCentreTestEjecteur(void);
void processusCentreTestVentouse(void);

void processusCentreModeOperation(void);
void processusCentreModeArret(void);
void processusCentreModeErreur(void);

void processusCentreModeAttente(void)
{
  	interfacePCF8574.mode = ATTENTE;
	//faire lecture des entrees pour assurer aucune erreur
	// si erreur -> mode erreur bloquant
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x55= init
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

    interfacePCF8574.mode = ARRET;
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
	interfacePCF8574.mode = TEST;
	serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
			processusCentreTestEntrees;
}

void processusCentreTestEntrees(void)
{
	//if ENTREES != EXPECTED
	// phaseCentre = ModeErreur;
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
		//activer verin position sortie
		CLEAR_EJECT_POS_ENTREE_SOLE719();
		SET_EJECT_POS_SORTIE_SOLE722();
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
		if ((interfacePCF8574.entreesCarte1 & ~0x95) != 0			//0x95 = init, sauf poussoir = sortie
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
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

	if (compteurVerin == TEMPS_MAXIMUM)
	{
		CLEAR_EJECT_POS_SORTIE_SOLE722();
		SET_EJECT_POS_ENTREE_SOLE719();
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

	if (compteurElevateur == TEMPS_MAXIMUM && ELEVATEUR_HAUT != 0)
	{
		compteurElevateur = 0; // reset prochain test
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_ELEV_HAUT_SOLE716();
		CLEAR_ELEV_BAS_SOLE713();
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
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x55 = init, convoyeur pas de sortie pour etat
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
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
		SET_POUSSOIR_POS_SORTIE_SOLE725();
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
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x59) != 0			//0x75 = init, sauf ejecteur = sortie
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
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

	if (compteurEjecteur >= TEMPS_MAXIMUM && ELEVATEUR_HAUT != 0)
	{
		compteurEjecteur = 0; // reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_POUSSOIR_POS_SORTIE_SOLE725();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestVentouse;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
}

void processusCentreTestVentouse(void)
{

}

void processusCentreModeOperation(void)
{
	interfacePCF8574.mode = OPERATION;
}

void processusCentreModeErreur(void)
{
	piloteTimer14_arreteLesInterruptions();
}

void processusCentreDeTri_Init(void)
{
	//initialiser sorties
	// toutes sorties = 0?

	serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeAttente;
}

