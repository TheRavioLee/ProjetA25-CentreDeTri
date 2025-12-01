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

uint8_t reverseByte(uint8_t x);

uint8_t reverseByte(uint8_t x)
{
    uint8_t r = 0;
    for (int i = 0; i < 8; i++)
    {
        r <<= 1;
        r |= (x & 1);
        x >>= 1;
    }
    return r;
}

void lectureEntrees(void)
{
	interfacePCF8574.entreesCarte1 = lectureI2C(ADDR_ENTREE_CARTE1);
	interfacePCF8574.entreesCarte2 = reverseByte(~lectureI2C(ADDR_ENTREE_CARTE2));
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
	interfacePCF8574.entreesCarte1 = 0x00;
	interfacePCF8574.entreesCarte2 = 0x00;
	interfacePCF8574.entreesCarte3 = 0x00;

	interfacePCF8574.sortiesCarte1 = 0x00;
	interfacePCF8574.sortiesCarte2 = 0x00;

	interfacePCF8574.information = INFORMATION_TRAITEE;
	interfacePCF8574.requete = REQUETE_ACTIVE;
//	serviceBaseDeTemps_execute[ENTREES_NUM_PHASE] = lectureEntrees;
//	serviceBaseDeTemps_execute[SORTIES_NUM_PHASE] = ecritureSorties;
}
