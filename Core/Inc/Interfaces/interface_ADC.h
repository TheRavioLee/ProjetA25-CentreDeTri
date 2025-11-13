/*
 * interface_ADC.h
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_INTERFACES_INTERFACE_ADC_H_
#define INC_INTERFACES_INTERFACE_ADC_H_

//bit shift de << 1 pour adresses de lecture I2C avec HAL
//I2C HAL fait automatiquement bit shift >> 1
#define ADDR_ANALOGUE1 (0x4D << 1)

typedef struct {
	uint8_t information;
	uint16_t valeurADC;
} INTERFACE_ADC;

extern INTERFACE_ADC interfaceADC;

void interfaceADC_init(void);

#endif /* INC_INTERFACES_INTERFACE_ADC_H_ */
