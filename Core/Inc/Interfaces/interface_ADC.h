/*
 * interface_ADC.h
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_INTERFACES_INTERFACE_ADC_H_
#define INC_INTERFACES_INTERFACE_ADC_H_

//bit shift de << 1 pour adresses de lecture I2C avec HAL
#define ADDR_ANALOGUE1 (0x4D << 1)

typedef struct {
	uint8_t information;
	uint16_t valeurADC;
} INTERFACE_ADC;

extern INTERFACE_ADC interfaceADC;


void lectureADC(void);
void interfaceADC_Init(void);

#endif /* INC_INTERFACES_INTERFACE_ADC_H_ */
