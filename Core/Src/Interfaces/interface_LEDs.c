/*
 * interface_LEDs.c
 *
 *  Created on: Dec 8, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "interface_LEDs.h"
#include "pilote_LED_J.h"
#include "pilote_LED_V.h"
#include "pilote_LED_R.h"

void allumerLED(uint8_t led)
{
	switch(led)
	{
	case LED_ROUGE:
		LEDRset();
		break;
	case LED_JAUNE:
		LEDJset();
		break;
	case LED_VERT:
		LEDVset();
		break;
	}
}

void eteindreLED(uint8_t led)
{
	switch(led)
	{
	case LED_ROUGE:
		LEDRreset();
		break;
	case LED_JAUNE:
		LEDJreset();
		break;
	case LED_VERT:
		LEDVreset();
		break;
	}
}

void clignoterLED(uint8_t led)
{
	static uint8_t compteurLED = 0;

	compteurLED++;

	if (compteurLED >= 50)
	{
		compteurLED = 0;

		switch(led)
		{
		case LED_ROUGE:
			LEDRtoggle();
			break;
		case LED_JAUNE:
			LEDJtoggle();
			break;
		case LED_VERT:
			LEDVtoggle();
			break;
		}
	}
}
