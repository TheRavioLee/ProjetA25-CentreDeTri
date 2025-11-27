/*
 * pilote_MoteurPH4.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_MoteurPH4.h"

void moteurPH4_set(void)
{
	HAL_GPIO_WritePin(PHASE_4_GPIO_Port, PHASE_4_Pin, GPIO_PIN_SET);
}

void moteurPH4_reset(void)
{
	HAL_GPIO_WritePin(PHASE_4_GPIO_Port, PHASE_4_Pin, GPIO_PIN_RESET);
}
