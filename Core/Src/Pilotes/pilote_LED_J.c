/*
 * pilote_LED_J.c
 *
 *  Created on: Dec 8, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_LED_J.h"


void LEDJset(void)
{
	HAL_GPIO_WritePin(LED_J_GPIO_Port, LED_J_Pin, GPIO_PIN_SET);
}

void LEDJreset(void)
{
	HAL_GPIO_WritePin(LED_J_GPIO_Port, LED_J_Pin, GPIO_PIN_RESET);
}

void LEDJtoggle(void)
{
	HAL_GPIO_TogglePin(LED_J_GPIO_Port, LED_J_Pin);
}
