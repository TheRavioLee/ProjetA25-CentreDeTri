/*
 * interface_BoutonBleu.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "interface_BoutonBleu.h"
#include "pilote_BoutonBleu.h"
#include "serviceBaseTemps.h"

//Defines prives
#define COMPTE_MAX_AVANT_LECTURE (FREQ_BASETEMPS_HZ/FREQ_LECTURE_BTN_HZ)
#define NOMBRE_MIN_LECTURE_PAR_DECISION 2

//Fonctions privees
void interfaceBtnBleu_gere(void);

//Variables privees
uint16_t compteurAvantLecture;
uint16_t compteurAntiRebond;



void interfaceBtnBleu_gere(void)
{
	compteurAvantLecture++;
	if(compteurAvantLecture < COMPTE_MAX_AVANT_LECTURE)
	{
		return;
	}
	compteurAvantLecture = 0;
	if(pilote_BoutonBleu_Lire() == BOUTON_APPUYE)
	{
		if(compteurAntiRebond == NOMBRE_MIN_LECTURE_PAR_DECISION)
		{
			return;
		}
		compteurAntiRebond++;
		if(compteurAntiRebond < NOMBRE_MIN_LECTURE_PAR_DECISION)
		{
			return;
		}
		interfaceBtnBleu.etatBouton = BOUTON_APPUYE;
		interfaceBtnBleu.information = INFORMATION_DISPONIBLE;
		return;
	}
	if(compteurAntiRebond == 0)
	{
		return;
	}
	compteurAntiRebond--;
	if(compteurAntiRebond > 0)
	{
		return;
	}
	interfaceBtnBleu.etatBouton = BOUTON_RELACHE;
	interfaceBtnBleu.information = INFORMATION_DISPONIBLE;
}

//Variables publiques
INTERFACE_BTN_BLEU interfaceBtnBleu;

//Fonctions publiques
void interface_BoutonBleuInit()
{
	interfaceBtnBleu.information = INFORMATION_TRAITEE;
	interfaceBtnBleu.etatBouton = BOUTON_INCONNU;
	compteurAvantLecture = 0;
	compteurAntiRebond = 1;

	serviceBaseDeTemps_execute[INTERFACE_BTN_BLEU_PHASE] =
			interfaceBtnBleu_gere;
}
