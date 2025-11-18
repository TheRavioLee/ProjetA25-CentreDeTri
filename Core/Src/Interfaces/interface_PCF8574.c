/*
 * interface_PCF8574.c
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#include "main.h"
#include "serviceBaseTemps.h"
#include "pilote_I2C.h"
#include "interface_PCF8574.h"

extern I2C_HandleTypeDef hi2c1;

void lectureEntrees(void)
{
	static uint8_t temp1;
	static uint8_t temp2;
	static uint8_t temp3;

////	if(interfacePCF8574.information == INFORMATION_DISPONIBLE)
//	{
//		return;
//	}

	if(HAL_I2C_Master_Receive(&hi2c1, ADDR_ENTREE_CARTE1, &temp1, 1, 1) == HAL_OK)
	{
		interfacePCF8574.entreesCarte1 = temp1;
	}
	if(HAL_I2C_Master_Receive(&hi2c1, ADDR_ENTREE_CARTE2, &temp2, 1, 1) == HAL_OK)
	{
		interfacePCF8574.entreesCarte2 = temp2;
	}
	if(HAL_I2C_Master_Receive(&hi2c1, ADDR_ENTREE_CARTE3, &temp3, 1, 1) == HAL_OK)
	{
		interfacePCF8574.entreesCarte3 = temp3;
	}
//	interfacePCF8574.information = INFORMATION_DISPONIBLE;
}

void ecritureSorties(void)
{
	// inversion pour ecriture logique 1=1, 0=0
	uint8_t out1 = interfacePCF8574.sortiesCarte1;
	uint8_t out2 = interfacePCF8574.sortiesCarte2;

	HAL_I2C_Master_Transmit(&hi2c1, ADDR_SORTIE_CARTE1, &out1, 1, 1);
	HAL_I2C_Master_Transmit(&hi2c1, ADDR_SORTIE_CARTE2, &out2, 1, 1);

}

//variables publiques
INTERFACE_PCF8574 interfacePCF8574;

//fonctions publiques
void interfacePCF8574_init(void)
{
//	serviceBaseDeTemps_execute[ENTREES_NUM_PHASE] = lectureEntrees;
//	serviceBaseDeTemps_execute[SORTIES_NUM_PHASE] = ecritureSorties;
}
