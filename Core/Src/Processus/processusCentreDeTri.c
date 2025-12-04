/*
 * processusCentreDeTri.c
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_Timers.h"
#include "ServiceBaseTemps.h"
#include "interface_ADC.h"
#include "interface_PCF8574.h"
#include "interface_BoutonBleu.h"
#include "processusEntreesNumeriques.h"
#include "processusEntreeAnalogique.h"
#include "processusSortiesNumeriques.h"
#include "processusCentreDeTri.h"

//Definitions privees
#define BOUTON_BLEU interfaceBtnBleu.etatBouton
#define INFO_BTN_BLEU interfaceBtnBleu.information

#define TEMPS_MAXIMUM 100 // 250 * 9ms = ~2.5s

uint8_t requetePosition;

CENTRE_DE_TRI centreDeTri;

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
void processusCentreTestDeplaceVentouse(void);

void processusCentreModeOperation(void);

void processusCentreOperationDetectionBloc(void);
void processusCentreOperationElevateur(void);
void processusCentreOperationConvoyeur(void);
void processusCentreOperationPont(void);

void processusCentreModeArret(void);
void processusCentreModeErreur(void);

void processusCentreModeAttente(void)
{
	static uint8_t compteurPont = 0;
	centreDeTri.mode = ATTENTE;
	//faire lecture des entrees pour assurer aucune erreur
	// si erreur -> mode erreur bloquant
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x55= init
				|| (interfacePCF8574.entreesCarte2 & ~0x34) != 0	//0x30 = init, sauf boutons rouge/vert
				|| (interfacePCF8574.entreesCarte3 & 0x02) == 0) 	//0x02 = init, bit 2 = 0 = error
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfaceADC.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (requetePosition == REQUETE_ACTIVE)
	{
	    compteurPont++;

	    if (compteurPont == 1)
	    {
	    	interfacePCF8574.requete = REQUETE_ACTIVE;
	        SET_START_POS_PROCESS();   // start of pulse
	    }

	    // ensure at least N cycles before checking DEF_MOTION_COMPLETE
	    if (compteurPont >= TEMPS_MAXIMUM && DEF_MOTION_COMPLETE != 0)
	    {
	    	interfacePCF8574.requete = REQUETE_ACTIVE;
	        CLEAR_START_POS_PROCESS(); // end pulse
	        requetePosition = REQUETE_TRAITEE;
	        compteurPont = 0;
	    }
	}


	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (INFO_BTN_BLEU == INFORMATION_DISPONIBLE && BOUTON_BLEU == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfaceADC.information = INFORMATION_TRAITEE;
		INFO_BTN_BLEU = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeTest;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
	{

		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfaceADC.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_LUMIERE_VERTE();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeOperation;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreModeArret(void)
{
    static uint8_t compteurAppuye = 0;
    static uint16_t timerDoublePress = 0;

    static uint8_t etatStable = BOUTON_RELACHE;      // debounced state
    static uint8_t compteurStabilite = 0;            // debounce counter

    uint8_t etatBrut = BOUTON_VERT;                  // 0 or 1

    centreDeTri.mode = ARRET;
    interfacePCF8574.information = INFORMATION_TRAITEE;
    interfaceADC.information = INFORMATION_TRAITEE;

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
	centreDeTri.mode = TEST;
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
			interfaceADC.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_EJECT_POS_ENTREE_SOLE719();
		CLEAR_EJECT_POS_SORTIE_SOLE722();
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestVerinMagasin;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreTestVerinMagasin(void)
{
	static uint16_t compteurVerin = 0;

	compteurVerin++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x59) != 0			//0x59 = init, sauf poussoir = sortie
				|| (interfacePCF8574.entreesCarte2 & ~0x34) != 0) 	//0x30 = init sauf boutons rouge/vert, capteur optique
		{
			compteurVerin = 0; // reset pour prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfaceADC.information = INFORMATION_TRAITEE;
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
		SET_EJECT_POS_SORTIE_SOLE722();
		CLEAR_EJECT_POS_ENTREE_SOLE719();
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (compteurVerin == TEMPS_MAXIMUM)
	{
		SET_EJECT_POS_SORTIE_SOLE722();
		CLEAR_EJECT_POS_ENTREE_SOLE719();
		return;
	}

	if (compteurVerin > TEMPS_MAXIMUM)
	{
		if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
		{
			compteurVerin = 0; // reset pour prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfacePCF8574.requete = REQUETE_ACTIVE;
			SET_ELEV_HAUT_SOLE716();
			CLEAR_ELEV_BAS_SOLE713();
			interfaceADC.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreTestElevateur;
		}
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreTestElevateur(void)
{
	static uint16_t compteurElevateur = 0;

	compteurElevateur++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x7D) != 0			//0x75 = init, sauf elevateur = haut
				|| (interfacePCF8574.entreesCarte2 & ~0x35) != 0) 	//0x30 = init sauf boutons rouge/vert
		{
			compteurElevateur = 0; // reset prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfaceADC.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		compteurElevateur = 0; // reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfaceADC.information = INFORMATION_TRAITEE;
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
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestConvoyeur;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreTestConvoyeur(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x75) != 0			//0x75 = init, convoyeur pas de sortie; suppose que temps elevateur = haut trop grand pour
				|| (interfacePCF8574.entreesCarte2 & ~0x3F) != 0) 	//0x30 = init sauf boutons rouge/vert|  detecter avant prochaine phase
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfaceADC.information = INFORMATION_TRAITEE;
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
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_RELAIS_MOTEUR_CONVOYEUR();
		SET_POUSSOIR_POS_SORTIE_SOLE725();
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestEjecteur;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreTestEjecteur(void)
{
	static uint16_t compteurEjecteur = 0;

	compteurEjecteur++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{		//CHANGER POUR VRAI TEST -> 0x59??
		if ((interfacePCF8574.entreesCarte1 & ~0x95) != 0			//0x59 = init, sauf ejecteur = sortie
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
		{
			compteurEjecteur = 0; // reset prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfaceADC.information = INFORMATION_TRAITEE;
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
		CLEAR_POUSSOIR_POS_SORTIE_SOLE725();
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeArret;
		return;
	}

	if (compteurEjecteur >= TEMPS_MAXIMUM && POUSSOIR_POS_SORTIE != 0)
	{
		compteurEjecteur = 0; // reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_POUSSOIR_POS_SORTIE_SOLE725();
		SET_VACCUM_SOLE710();
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestVentouseVaccum;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreTestVentouseVaccum(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x55 = init
				|| (interfacePCF8574.entreesCarte2 & ~0x70) != 0)	//0x70 = init, sauf boutons rouge/vert et vaccum ventouse
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfaceADC.information = INFORMATION_TRAITEE;
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
		interfaceADC.information = INFORMATION_TRAITEE;
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
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestVentouseHauteur;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreTestVentouseHauteur(void)
{
	static uint16_t compteurVentouseHauteur = 0;

	compteurVentouseHauteur++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{	//CHANGER POUR VRAI TEST -> 0X56??
		if ((interfacePCF8574.entreesCarte1 & ~0x56) != 0			//0x56 = init, sauf ventouse = bas
				|| (interfacePCF8574.entreesCarte2 & ~0x38) != 0)	//0x70 = init, sauf boutons rouge/vert
		{
			compteurVentouseHauteur = 0; //reset prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			interfaceADC.information = INFORMATION_TRAITEE;
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
		interfaceADC.information = INFORMATION_TRAITEE;
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
		interfaceADC.information = INFORMATION_TRAITEE;
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreTestDeplaceVentouse;
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreTestDeplaceVentouse(void)
{
	static uint8_t compteurBoutonVert = 0;
	static uint8_t compteurDeplacement = 0;
	static uint8_t sender = 0;

	if (requetePosition == REQUETE_ACTIVE)
	{
		compteurDeplacement++;

		if (compteurDeplacement == 1)
		{
			interfacePCF8574.requete = REQUETE_ACTIVE;
			SET_START_POS_PROCESS();   // start of pulse
			return;
		}

		// ensure at least N cycles before checking DEF_MOTION_COMPLETE
		if (compteurDeplacement >= TEMPS_MAXIMUM && DEF_MOTION_COMPLETE != 0)
		{
			interfacePCF8574.requete = REQUETE_ACTIVE;
			CLEAR_START_POS_PROCESS(); // end pulse
			requetePosition = REQUETE_TRAITEE;
			compteurDeplacement = 0;
			switch(sender)
			{
			case 1:
				serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
						processusCentreModeArret;
				interfacePCF8574.information = INFORMATION_TRAITEE;
				interfaceADC.information = INFORMATION_TRAITEE;
				return;
				break;
			case 2:
				if (compteurBoutonVert == 3)
				{
					compteurBoutonVert = 0;
					serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
							processusCentreModeAttente;
				}
				interfacePCF8574.information = INFORMATION_TRAITEE;
				interfaceADC.information = INFORMATION_TRAITEE;
				return;
				break;
			}
		}
		interfacePCF8574.information = INFORMATION_TRAITEE;
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{	//CHANGER POUR VRAI TEST -> 0X56??
		if ((interfacePCF8574.entreesCarte1 & ~0x55) != 0			//0x56 = init, sauf ventouse = bas
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0	//0x30 = init, sauf boutons rouge/vert
				|| (interfacePCF8574.entreesCarte3 & 0x02) == 0)	//0x02 = init, bit 2 = 0 = error
		{
			compteurBoutonVert = 0; //reset prochain test
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_ROUGE == BOUTON_APPUYE)
	{
		compteurBoutonVert = 0; //reset prochain test
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_SELECT_POS_0();
		CLEAR_SELECT_POS_1();
		CLEAR_SELECT_POS_2();
		SET_START_POS_PROCESS();
		sender = 1;	//BOUTON_ROUGE
		return;
	}

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE && BOUTON_VERT == BOUTON_APPUYE
			&& DEF_MOTION_COMPLETE != 0)
	{
		compteurBoutonVert++;
		interfaceADC.information = INFORMATION_TRAITEE;
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		requetePosition = REQUETE_ACTIVE;

		switch(compteurBoutonVert)
		{
		case 1:
			CLEAR_SELECT_POS_0();
			SET_SELECT_POS_1();
			CLEAR_SELECT_POS_2();
			CLEAR_START_POS_PROCESS();
			break;
		case 2:
			CLEAR_SELECT_POS_0();
			CLEAR_SELECT_POS_1();
			SET_SELECT_POS_2();
			CLEAR_START_POS_PROCESS();
			break;
		case 3:
			SET_SELECT_POS_0();
			CLEAR_SELECT_POS_1();
			CLEAR_SELECT_POS_2();
			CLEAR_START_POS_PROCESS();
			break;
		}
		sender = 2; //BOUTON_VERT
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE; //si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreModeOperation(void)
{
	centreDeTri.mode = OPERATION;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0xD5) != 0			//0x55= init
				|| (interfacePCF8574.entreesCarte2 & ~0x37) != 0	//0x30 = init, sauf boutons rouge/vert
				|| (interfacePCF8574.entreesCarte3 & 0x02) == 0) 	//0x02 = init, bit 2 = 0 = error
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (POUSSOIR_POS_ENTREE == 1 && POUSSOIR_POS_SORTIE != 1)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_POUSSOIR_POS_SORTIE_SOLE725();
	}
	else if (POUSSOIR_POS_ENTREE != 1 && POUSSOIR_POS_SORTIE == 1)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_POUSSOIR_POS_SORTIE_SOLE725();
		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreOperationDetectionBloc;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE;	//si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreOperationDetectionBloc(void)
{
	static uint8_t compteurBloc = 0;

	compteurBloc++;

	if (compteurBloc >= TEMPS_MAXIMUM)
	{
		compteurBloc = 0;
		switch (interfacePCF8574.entreesCarte2 & 0x07)
		{
		case 0x02:
			centreDeTri.couleurBloc = BLOC_NOIR;
			break;
		case 0x06:
			centreDeTri.couleurBloc = BLOC_ORANGE;
			break;
		case 0x07:
			centreDeTri.couleurBloc = BLOC_METAL;
			break;
		default:
			centreDeTri.couleurBloc = 0;
			//si pas de bloc?
			break;
		}
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfaceADC.information = INFORMATION_TRAITEE;
	}

	if (centreDeTri.couleurBloc != 0)
	{
		interfacePCF8574.information = INFORMATION_TRAITEE;
		interfaceADC.information = INFORMATION_TRAITEE;
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_ELEV_BAS_SOLE713();
		SET_ELEV_HAUT_SOLE716();

		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreOperationElevateur;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE;	//si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreOperationElevateur(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x75) != 0			//0x55= init
				|| (interfacePCF8574.entreesCarte2 & ~0x37) != 0	//0x30 = init, sauf boutons rouge/vert
				|| (interfacePCF8574.entreesCarte3 & 0x02) == 0) 	//0x02 = init, bit 2 = 0 = error
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (ELEVATEUR_BAS == 1 && ELEVATEUR_HAUT != 1)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_ELEV_HAUT_SOLE716();
		CLEAR_ELEV_BAS_SOLE713();
	}
	else if (ELEVATEUR_BAS != 1 && ELEVATEUR_HAUT == 1 && interfaceADC.valeurADC >= 0x350)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_RELAIS_MOTEUR_CONVOYEUR();

		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreOperationConvoyeur;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE;	//si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreOperationConvoyeur(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x7D) != 0			//0x55= init
				|| (interfacePCF8574.entreesCarte2 & ~0x3F) != 0	//0x30 = init, sauf boutons rouge/vert
				|| (interfacePCF8574.entreesCarte3 & 0x02) == 0) 	//0x02 = init, bit 2 = 0 = error
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (ELEVATEUR_BAS != 1 && ELEVATEUR_HAUT == 1 && interfaceADC.valeurADC >= 0x350)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_EJECT_POS_ENTREE_SOLE719();
		CLEAR_EJECT_POS_SORTIE_SOLE722();
	}

	if (DETECT_OPT_CHUTE == 1)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		CLEAR_EJECT_POS_ENTREE_SOLE719();
		SET_EJECT_POS_SORTIE_SOLE722();
		CLEAR_RELAIS_MOTEUR_CONVOYEUR();
		CLEAR_ELEV_HAUT_SOLE716();
		SET_ELEV_BAS_SOLE713();

		serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreOperationPont;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE;	//si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
}

void processusCentreOperationPont(void)
{
	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0x57) != 0			//0x55= init
				|| (interfacePCF8574.entreesCarte2 & ~0x38) != 0	//0x30 = init, sauf boutons rouge/vert
				|| (interfacePCF8574.entreesCarte3 & 0x02) == 0) 	//0x02 = init, bit 2 = 0 = error
		{
			interfacePCF8574.information = INFORMATION_TRAITEE;
			serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
					processusCentreModeErreur;
			return;
		}
	}

	if (DETECT_OPT_CHUTE == 1 && VENTOUSE_HAUT == 1)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_VENTOUSE_BAS_SOLE704();
		CLEAR_VENTOUSE_HAUT_SOLE707();
	}

	if (DETECT_OPT_CHUTE == 1 && VENTOUSE_BAS == 1)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;
		SET_VACCUM_SOLE710();
		CLEAR_VENTOUSE_BAS_SOLE704();
		SET_VENTOUSE_HAUT_SOLE707();
	}

	if (DETECT_OPT_CHUTE != 1 && VENTOUSE_HAUT == 1 && INDIC_PRESS_VENTOUSE == 1)
	{
		interfacePCF8574.requete = REQUETE_ACTIVE;

		switch (centreDeTri.couleurBloc)
		{
		case BLOC_NOIR:

			break;
		case BLOC_ORANGE:
			break;
		case BLOC_METAL:
			break;
		}
	}

	interfacePCF8574.information = INFORMATION_TRAITEE;	//si changement mais aucune condition -> lecture encore
	interfaceADC.information = INFORMATION_TRAITEE;
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
	CLEAR_EJECT_POS_ENTREE_SOLE719();
	SET_EJECT_POS_SORTIE_SOLE722();
	CLEAR_POUSSOIR_POS_SORTIE_SOLE725();
	CLEAR_RELAIS_MOTEUR_CONVOYEUR();

	SET_CONTROLLER_RELEASE();
	SET_SELECT_POS_0();
	CLEAR_SELECT_POS_1();
	CLEAR_SELECT_POS_2();
	CLEAR_START_POS_PROCESS();
	requetePosition = REQUETE_ACTIVE;

	centreDeTri.couleurBloc = 0;
	centreDeTri.information = INFORMATION_TRAITEE;
	centreDeTri.mode = ATTENTE;
	centreDeTri.requete = REQUETE_TRAITEE;

	serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
				processusCentreModeAttente;
}

