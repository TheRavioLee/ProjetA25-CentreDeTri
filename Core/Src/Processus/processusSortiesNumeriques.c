/*
 * processusSortiesNumeriques.c
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "serviceBaseTemps.h"
#include "interface_PCF8574.h"

void processusSortiesNum_Ecrire(void);

void processusSortiesNum_Ecrire(void)
{
	if (interfacePCF8574.requete == REQUETE_ACTIVE)
	{
		ecritureSorties();
		interfacePCF8574.requete = REQUETE_TRAITEE;
	}
}

void processusSortiesNum_Init(void)
{
	serviceBaseDeTemps_execute[SORTIES_NUM_PHASE] =
				processusSortiesNum_Ecrire;
}
