/*
 * pilote_Timer14_1ms.c
 *
 *  Created on: May 21, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_Timer14.h"
//Declarations de fonctions privees:
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

//Definitions de variables privees:
extern TIM_HandleTypeDef htim14; //definie par le hal et declare ici


//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
void (*piloteTimer14_execute)(void);

//Definitions de fonctions publiques:
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim14)
  {
	  piloteTimer14_execute();
  }
}

void piloteTimer14_permetLesInterruptions(void)
{
  HAL_TIM_Base_Start_IT(&htim14);
}

void piloteTimer14_initialise(void)
{
  piloteTimer14_execute = doNothing;
}
