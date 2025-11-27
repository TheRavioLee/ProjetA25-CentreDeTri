/*
 * pilote_MoteurPH3.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_MoteurPH3.h"

void moteurPH3_set(void)
{
	HAL_GPIO_WritePin(PHASE_3_GPIO_Port, PHASE_3_Pin, GPIO_PIN_SET);
}

void moteurPH3_reset(void)
{
	HAL_GPIO_WritePin(PHASE_3_GPIO_Port, PHASE_3_Pin, GPIO_PIN_RESET);
}
