/*
 * pilote_BoutonBleu.c
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "pilote_BoutonBleu.h"

//Fonctions publiques
uint8_t pilote_BoutonBleu_Lire(void)
{
	return HAL_GPIO_ReadPin(BTN_BLEU_GPIO_Port, BTN_BLEU_Pin);
}

