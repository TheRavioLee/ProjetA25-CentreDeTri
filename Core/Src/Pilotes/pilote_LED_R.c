/*
 * pilote_LED_R.c
 *
 *  Created on: Dec 8, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_LED_R.h"


void LEDRset(void)
{
	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
}

void LEDRreset(void)
{
	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
}

void LEDRtoggle(void)
{
	HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
}
