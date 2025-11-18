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
	interfacePCF8574.sortiesCarte1 = ~0x01;
	interfacePCF8574.sortiesCarte2 = ~0x80;
	ecritureSorties();
}

void processusSortiesNum_Init(void)
{
	serviceBaseDeTemps_execute[SORTIES_NUM_PHASE] =
				processusSortiesNum_Ecrire;
}
