/*
 * ServiceBaseTemps_1ms.c
 *
 *  Created on: May 21, 2025
 *      Author: thomaslajoie
 */

#include <pilote_Timers.h>
#include "ServiceBaseTemps.h"
#include "main.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
void serviceBaseDeTemps_gere(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void serviceBaseDeTemps_gere(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i]();
  }
}

//Definitions de variables publiques:
void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

//Definitions de fonctions publiques:
void serviceBaseDeTemps_initialise(void)
{
unsigned char i;
  for (i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++)
  {
    serviceBaseDeTemps_execute[i] = doNothing;
  }
  piloteTimer14_execute = serviceBaseDeTemps_gere;
}
