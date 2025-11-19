/*
 * interface_PCF8574.c
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#include "main.h"
#include "serviceBaseTemps.h"
#include "pilote_I2C.h"
#include "interface_PCF8574.h"

void lectureEntrees(void)
{
	interfacePCF8574.entreesCarte1 = lectureI2C(ADDR_ENTREE_CARTE1);
	interfacePCF8574.entreesCarte2 = ~lectureI2C(ADDR_ENTREE_CARTE2);
	interfacePCF8574.entreesCarte3 = ~lectureI2C(ADDR_ENTREE_CARTE3);
}

void ecritureSorties(void)
{
	ecritureI2C(ADDR_SORTIE_CARTE1, interfacePCF8574.sortiesCarte1);
	ecritureI2C(ADDR_SORTIE_CARTE2, interfacePCF8574.sortiesCarte2);
}

//variables publiques
INTERFACE_PCF8574 interfacePCF8574;

//fonctions publiques
void interfacePCF8574_init(void)
{
//	serviceBaseDeTemps_execute[ENTREES_NUM_PHASE] = lectureEntrees;
//	serviceBaseDeTemps_execute[SORTIES_NUM_PHASE] = ecritureSorties;
}
