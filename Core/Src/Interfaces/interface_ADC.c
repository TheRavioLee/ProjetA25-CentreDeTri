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

void lectureADC(void)
{
	interfaceADC.valeurADC = lectureI2C_10bits(ADDR_ANALOGUE1);
}

//variables publiques
INTERFACE_ADC interfaceADC;

//fonctions publiques
void interfaceADC_Init(void)
{
	interfaceADC.information = INFORMATION_TRAITEE;
}
