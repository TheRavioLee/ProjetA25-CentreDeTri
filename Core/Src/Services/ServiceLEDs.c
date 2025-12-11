/*
 * ServiceLEDs.c
 *
 *  Created on: Dec 11, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "interface_LEDs.h"
#include "processusCentreDeTri.h"
#include "ServiceBaseTemps.h"
#include "processusEntreesNumeriques.h"
#include "interface_PCF8574.h"
#include "interface_ADC.h"

void serviceLEDs_gere(void);

void serviceLEDs_gere(void)
{
	switch(centreDeTri.mode)
	{
	case ATTENTE:
		clignoterLED(LED_VERT);
		eteindreLED(LED_ROUGE);
		eteindreLED(LED_JAUNE);
		break;
	case OPERATION:
		if (centreDeTri.couleurBloc != 0)
		{
			switch (centreDeTri.couleurBloc)
			{
			case BLOC_NOIR:
				clignoterLED(LED_JAUNE);
				eteindreLED(LED_ROUGE);
				eteindreLED(LED_VERT);
				break;
			case BLOC_ORANGE:
				allumerLED(LED_JAUNE);
				eteindreLED(LED_ROUGE);
				eteindreLED(LED_VERT);
				break;
			case BLOC_METAL:
				allumerLED(LED_JAUNE);
				eteindreLED(LED_ROUGE);
				eteindreLED(LED_VERT);
				break;
			}
		}
		break;
	case ARRET:
		allumerLED(LED_ROUGE);
		eteindreLED(LED_JAUNE);
		eteindreLED(LED_VERT);
		break;
	case TEST:
		if (DETECT_MAGNETIQUE != 0)
		{
			allumerLED(LED_JAUNE);
			eteindreLED(LED_ROUGE);
			eteindreLED(LED_VERT);
			return;
		}
		else if (DETECT_CAPACITIF != 0)
		{
			allumerLED(LED_ROUGE);
			eteindreLED(LED_JAUNE);
			eteindreLED(LED_VERT);
			return;
		}
		else if (DETECT_OPT_PLATEAU  != 0)
		{
			allumerLED(LED_VERT);
			eteindreLED(LED_JAUNE);
			eteindreLED(LED_ROUGE);
			return;
		}
		else if (DETECT_OPT_CHUTE != 0)
		{
			allumerLED(LED_VERT);
			eteindreLED(LED_JAUNE);
			eteindreLED(LED_ROUGE);
			return;
		}
		else if (interfaceADC.valeurADC >= 0x050)
		{
			allumerLED(LED_JAUNE);
			allumerLED(LED_ROUGE);
			eteindreLED(LED_VERT);
		}
		else
		{
			eteindreLED(LED_JAUNE);
			eteindreLED(LED_ROUGE);
			eteindreLED(LED_VERT);
		}
		break;
	case ERREUR:
		clignoterLED(LED_ROUGE);
		eteindreLED(LED_VERT);
		eteindreLED(LED_JAUNE);
		break;
	}
}

void serviceLEDsInit(void)
{
	serviceBaseDeTemps_execute[LEDS_PHASE] =
			serviceLEDs_gere;
}

