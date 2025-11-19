/*
 * pilote_MoteurPH1.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_MoteurPH1.h"

void moteurPH1_set(void)
{
	HAL_GPIO_WritePin(PHASE_1_GPIO_Port, PHASE_1_Pin, GPIO_PIN_SET);
}

void moteurPH1_reset(void)
{
	HAL_GPIO_WritePin(PHASE_1_GPIO_Port, PHASE_1_Pin, GPIO_PIN_RESET);
}
