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

#define TEMPS_MAXIMUM 250

//Fonctions privees
void processusCentreModeAttente(void);
void processusCentreModeTest(void);

void processusCentreTestEntrees(void);
void processusCentreTestVerinMagasin(void);

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
		interfacePCF8574.information = INFORMATION_TRAITEE;

		if ((interfacePCF8574.entreesCarte1 & ~0xD5) != 0			//0x55= init
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init, sauf boutons rouge/vert
		{
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


}

void processusCentreModeArret(void)
{
	static uint8_t compteurAppuye = 0;
	static uint8_t compteurAntiRebond = 0;
	static uint16_t timerDoublePress = 0;
	static uint8_t etatPrecedent = BOUTON_RELACHE;

	interfacePCF8574.mode = ARRET;

	if (interfacePCF8574.information != INFORMATION_DISPONIBLE)
	{
		return;
	}

	interfacePCF8574.information = INFORMATION_TRAITEE;

	if (BOUTON_VERT != etatPrecedent)
	{
		compteurAntiRebond = 3;
	}

	if (compteurAntiRebond > 0)
	{
		compteurAntiRebond--;
		etatPrecedent = BOUTON_VERT;
		return;
	}

	//Front montant detecte
	if (etatPrecedent == BOUTON_RELACHE && BOUTON_VERT == BOUTON_APPUYE)
	{
		compteurAppuye++;

		if (compteurAppuye == 1)
		{
			timerDoublePress = 0;
		}
		else if (compteurAppuye == 2)
		{
			if (timerDoublePress < 300)
			{
				serviceBaseDeTemps_execute[PROCESSUS_CENTRE_TRI_PHASE] =
								processusCentreModeAttente;

				compteurAppuye = 0;
				etatPrecedent = BOUTON_VERT;
				return;
			}
			else
			{
				compteurAppuye = 1;
				timerDoublePress = 0;
			}
		}
	}

	etatPrecedent = BOUTON_VERT;

	if (compteurAppuye > 0)
	{
		timerDoublePress += 10;
		if (timerDoublePress > 300)
		{
			compteurAppuye = 0;
		}
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
}

void processusCentreTestVerinMagasin(void)
{
	static uint16_t compteurVerin = 0;

	compteurVerin++;

	if (interfacePCF8574.information == INFORMATION_DISPONIBLE)
	{
		if ((interfacePCF8574.entreesCarte1 & ~0xD5) != 0			//0xD5 = init, sauf poussoir = sortie
				|| (interfacePCF8574.entreesCarte2 & ~0x30) != 0) 	//0x30 = init sauf boutons rouge/vert
		{
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
			interfacePCF8574.requete = REQUETE_ACTIVE;

		}
	}
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

