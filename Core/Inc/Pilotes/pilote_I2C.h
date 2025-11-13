/*
 * pilote_I2C.h
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_PILOTES_PILOTE_I2C_H_
#define INC_PILOTES_PILOTE_I2C_H_

uint8_t lectureI2C(uint8_t adresse, uint8_t *data);
uint8_t lectureI2C_10bits(uint8_t adresse, uint16_t *data);
uint8_t ecritureI2C(uint8_t adresse, uint8_t *data);


#endif /* INC_PILOTES_PILOTE_I2C_H_ */
