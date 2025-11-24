/*
 * interface_PCF8574.h
 *
 *  Created on: Nov 12, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_INTERFACES_INTERFACE_PCF8574_H_
#define INC_INTERFACES_INTERFACE_PCF8574_H_


//bit shift de << 1 pour adresses de lecture I2C avec HAL
#define ADDR_ENTREE_CARTE1 (0x38 << 1)	//carte entrees num Thomas
#define ADDR_ENTREE_CARTE2 (0x3A << 1)	//carte entrees num Anthony
#define ADDR_ENTREE_CARTE3 (0x3B << 1)	//carte entrees num Harold

#define ADDR_SORTIE_CARTE1 (0x3C << 1)
#define ADDR_SORTIE_CARTE2 (0x3D << 1)

typedef struct {
	uint8_t mode;
	uint8_t information;
	uint8_t requete;
	uint8_t entreesCarte1;
	uint8_t entreesCarte2;
	uint8_t entreesCarte3;
	uint8_t sortiesCarte1;
	uint8_t sortiesCarte2;
} INTERFACE_PCF8574;

extern INTERFACE_PCF8574 interfacePCF8574;

void interfacePCF8574_init(void);
void lectureEntrees(void);
void ecritureSorties(void);

#endif /* INC_INTERFACES_INTERFACE_PCF8574_H_ */
