/*
 * processus_Affichage.c
 *
 *  Created on: Oct 29, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "GLcd.h"
#include "processus_Affichage.h"
#include "ServiceBaseTemps.h"


void processusAffichage_Afficher(void)
{

}


AFFICHAGE affichageLCD;

void processusAffichageInit(void)
{
  HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_SET);

  HAL_Delay(100);
  vInitGLcd();
  HAL_Delay(100);
  vClearGLcd(0x00);

  serviceBaseDeTemps_execute[PROCESSUS_AFFICHAGE_PHASE] =
      processusAffichage_Afficher;
}
