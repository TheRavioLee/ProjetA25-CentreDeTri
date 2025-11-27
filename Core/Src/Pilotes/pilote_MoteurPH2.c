/*
 * pilote_MoteurPH2.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_MoteurPH2.h"

void moteurPH2_set(void)
{
	HAL_GPIO_WritePin(PHASE_2_GPIO_Port, PHASE_2_Pin, GPIO_PIN_SET);
}

void moteurPH2_reset(void)
{
	HAL_GPIO_WritePin(PHASE_2_GPIO_Port, PHASE_2_Pin, GPIO_PIN_RESET);
}
