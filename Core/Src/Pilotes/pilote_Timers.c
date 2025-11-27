/*
 * pilote_Timer14_1ms.c
 *
 *  Created on: May 21, 2025
 *      Author: thomaslajoie
 */
#include <pilote_Timers.h>
#include "main.h"
//Declarations de fonctions privees:
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

//Definitions de variables privees:
extern TIM_HandleTypeDef htim14; //definie par le hal et declare ici
extern TIM_HandleTypeDef htim2;

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
void (*piloteTimer14_execute)(void);

//Definitions de fonctions publiques:
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim14)
  {
	  piloteTimer14_execute();
  }
  if(htim == &htim2)
  {
	  //Timer pour detection passage par zero
	  //mettre compteur a 0 lors de passage a zero pour compter 100us
  }
}

void piloteTimer14_permetLesInterruptions(void)
{
  HAL_TIM_Base_Start_IT(&htim14);
}

void piloteTimer14_arreteLesInterruptions(void)
{
	HAL_TIM_Base_Stop_IT(&htim14);
}

void piloteTimer2_permetLesInterruptions(void)
{
  HAL_TIM_Base_Start_IT(&htim2);
}

void piloteTimers_initialise(void)
{
  piloteTimer14_execute = doNothing;
}
