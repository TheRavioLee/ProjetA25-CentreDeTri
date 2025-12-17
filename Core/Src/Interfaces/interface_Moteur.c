/*
 * interface_Moteur.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "serviceBaseTemps.h"
#include "pilote_MoteurPH1.h"
#include "pilote_MoteurPH2.h"
#include "pilote_MoteurPH3.h"
#include "pilote_MoteurPH4.h"
#include "interface_Moteur.h"

void gere_Moteur(void);
void controleMoteur(uint8_t ph1, uint8_t ph2, uint8_t ph3, uint8_t ph4);

uint8_t compteurMoteur;

uint8_t sequence_halfstep[8][4] = {
		{1,0,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,1,1},
		{0,0,0,1},
		{1,0,0,1}
};

void controleMoteur(uint8_t ph1, uint8_t ph2, uint8_t ph3, uint8_t ph4)
{
	ph1 == 1 ? moteurPH1_set() : moteurPH1_reset();
	ph2 == 1 ? moteurPH2_set() : moteurPH2_reset();
	ph3 == 1 ? moteurPH3_set() : moteurPH3_reset();
	ph4 == 1 ? moteurPH4_set() : moteurPH4_reset();
}

void gere_Moteur(void)
{
	static int8_t step_index = 0;

	if (interfaceMoteur.requete != REQUETE_ACTIVE)
	{
		return;
	}

	compteurMoteur++;

	if (compteurMoteur >= interfaceMoteur.vitesseMoteur)
	{
		interfaceMoteur.nombre_steps--;

		if (interfaceMoteur.nombre_steps == 0)
		{
			interfaceMoteur.requete = REQUETE_TRAITEE;
			return;
		}

		compteurMoteur = 0;

		step_index += interfaceMoteur.directionMoteur;

		if(step_index > 7) { step_index = 0; }
		if(step_index < 0) { step_index = 7; }

		controleMoteur(
				sequence_halfstep[step_index][0],
				sequence_halfstep[step_index][1],
				sequence_halfstep[step_index][2],
				sequence_halfstep[step_index][3]);
	}
}

INTERFACE_MOTEUR interfaceMoteur;

void interfaceMoteur_Init(void)
{
	moteurPH1_reset();
	moteurPH2_reset();
	moteurPH3_reset();
	moteurPH4_reset();


	interfaceMoteur.requete = REQUETE_ACTIVE;
	interfaceMoteur.directionMoteur = MONTER;
	interfaceMoteur.vitesseMoteur = VITESSE_RAPIDE;
	compteurMoteur = 0;
	interfaceMoteur.nombre_steps = STEPS_LONGUEUR_TOTALE;
	serviceBaseDeTemps_execute[MOTEUR_PHASE] = gere_Moteur;
}
