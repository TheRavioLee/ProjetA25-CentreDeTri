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
	lectureEntrees();
}

void processusEntreesNum_Init(void)
{
	serviceBaseDeTemps_execute[ENTREES_NUM_PHASE] =
			processusEntreesNum_Lire;
}
