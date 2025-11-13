/*
 * interface_ADC.c
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#include "main.h"
#include "serviceBaseTemps.h"
#include "pilote_I2C.h"
#include "interface_ADC.h"

//Declaration fonctions privees
void lectureADC(void);

void lectureADC(void)
{
	if(interfaceADC.information == INFORMATION_DISPONIBLE)
	{
		return;
	}

	lectureI2C_10bits(ADDR_ANALOGUE1, &interfaceADC.valeurADC);
	interfaceADC.information = INFORMATION_DISPONIBLE;
}

//variables publiques
INTERFACE_ADC interfaceADC;

//fonctions publiques
void interfaceADC_init(void)
{
	interfaceADC.information = INFORMATION_DISPONIBLE;
	serviceBaseDeTemps_execute[ENTREE_ANALOGUE_PHASE] = lectureADC;
}
