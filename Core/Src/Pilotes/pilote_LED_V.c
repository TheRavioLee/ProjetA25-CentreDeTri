/*
 * pilote_LED_V.c
 *
 *  Created on: Dec 8, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_LED_V.h"


void LEDVset(void)
{
	HAL_GPIO_WritePin(LED_V_GPIO_Port, LED_V_Pin, GPIO_PIN_SET);
}

void LEDVreset(void)
{
	HAL_GPIO_WritePin(LED_V_GPIO_Port, LED_V_Pin, GPIO_PIN_RESET);
}

void LEDVtoggle(void)
{
	HAL_GPIO_TogglePin(LED_V_GPIO_Port, LED_V_Pin);
}
