/*
 * processusEntreeAnalogique.c
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "serviceBaseTemps.h"
#include "interface_ADC.h"
#include "processusEntreeAnalogique.h"

void processusEntreeAnalogique_Lire(void);

void processusEntreeAnalogique_Lire(void)
{
	uint8_t valeurAnalogique = interfaceADC.valeurADC;

	if (interfaceADC.information != INFORMATION_DISPONIBLE)
	{
		lectureADC();
	}

	if (valeurAnalogique != interfaceADC.valeurADC)
	{
		interfaceADC.information = INFORMATION_DISPONIBLE;
	}
}

void processusEntreeAnalogique_Init(void)
{
	serviceBaseDeTemps_execute[ENTREE_ANALOGUE_PHASE] =
			processusEntreeAnalogique_Lire;
}

