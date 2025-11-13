/*
 * pilote_I2C.c
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#include "main.h"
#include "pilote_I2C.h"

extern I2C_HandleTypeDef hi2c1;


uint8_t lectureI2C(uint8_t adresse, uint8_t *data)
{
	uint8_t temp;

	if(HAL_I2C_Master_Receive(&hi2c1, adresse, &temp, 1, 1) == HAL_OK)
	{
		*data = temp;
		return READ_GOOD;
	}
	else
	{
		return READ_FAIL;
	}
}

uint8_t lectureI2C_10bits(uint8_t adresse, uint16_t *data)
{
	uint8_t buffer[2];
	uint16_t temp;

	if(HAL_I2C_Master_Receive(&hi2c1, adresse, buffer, 2, 1) == HAL_OK)
	{
		// Byte 1: [0 0 0 0 D9 D8 D7 D6]
		// Byte 2: [D5 D4 D3 D2 D1 D0 X X]
		temp = ((buffer[0] & 0x0F) << 6) | (buffer[1] >> 2);
		*data = temp;
		return READ_GOOD;
	}
	else
	{
		return READ_FAIL;
	}

}

uint8_t ecritureI2C(uint8_t adresse, uint8_t *data)
{
	if(HAL_I2C_Master_Transmit(&hi2c1, adresse, &data, 1, 1) == HAL_OK)
	{
		return WRITE_GOOD;
	}
	else
	{
		return WRITE_FAIL;
	}
}
