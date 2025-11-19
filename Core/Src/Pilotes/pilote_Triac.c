/*
 * pilote_Triac.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_Triac.h"




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == TRIAC_EXTI_Pin)
	{

	}
}


void piloteTriac_setCTRL(void)
{
	HAL_GPIO_WritePin(TRIAC_CTRL_GPIO_Port, TRIAC_CTRL_Pin, GPIO_PIN_RESET);
}

void piloteTriac_resetCTRL(void)
{
	HAL_GPIO_WritePin(TRIAC_CTRL_GPIO_Port, TRIAC_CTRL_Pin, GPIO_PIN_SET);
}
