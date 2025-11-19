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

void simuleMoteur(void);

uint16_t compteurMoteur;
uint8_t phase;


void simuleMoteur(void)
{
	compteurMoteur++;

	if (compteurMoteur == 50)
	{
		compteurMoteur = 0;

		switch(phase)
		{
		case 1:
			moteurPH4_reset();
			moteurPH1_set();
			break;
		case 2:
			moteurPH1_reset();
			moteurPH2_set();
			break;
		case 3:
			moteurPH2_reset();
			moteurPH3_set();
			break;
		case 4:
			moteurPH3_reset();
			moteurPH4_set();
			break;
		}

		if(phase == 4)
		{
			phase = 1;
		}
		else
		{
			phase++;
		}
	}
}

void interfaceMoteur_Init(void)
{
	moteurPH1_reset();
	moteurPH2_reset();
	moteurPH3_reset();
	moteurPH4_reset();

	phase = 1;
	compteurMoteur = 0;
	serviceBaseDeTemps_execute[MOTEUR_PHASE] = simuleMoteur;
}
