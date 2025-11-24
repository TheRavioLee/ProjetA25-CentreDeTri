/*
 * processusEntreesNumeriques.c
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "serviceBaseTemps.h"
#include "interface_PCF8574.h"

//fonctions privees
void processusEntreesNum_Lire(void);

void processusEntreesNum_Lire(void)
{
	uint8_t carteEntrees1 = interfacePCF8574.entreesCarte1;
	uint8_t carteEntrees2 = interfacePCF8574.entreesCarte2;
	uint8_t carteEntrees3 = interfacePCF8574.entreesCarte3;

	if (interfacePCF8574.information != INFORMATION_DISPONIBLE)
	{
		lectureEntrees();
	}

	if (carteEntrees1 != interfacePCF8574.entreesCarte1
			|| carteEntrees2 != interfacePCF8574.entreesCarte2
			|| carteEntrees3 != interfacePCF8574.entreesCarte3)
	{
		interfacePCF8574.information = INFORMATION_DISPONIBLE;
	}
}

void processusEntreesNum_Init(void)
{
	serviceBaseDeTemps_execute[ENTREES_NUM_PHASE] =
			processusEntreesNum_Lire;
}
