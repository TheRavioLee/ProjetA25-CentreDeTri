/*
 * interface_BoutonBleu.h
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_INTERFACES_INTERFACE_BOUTONBLEU_H_
#define INC_INTERFACES_INTERFACE_BOUTONBLEU_H_


typedef struct
{
	uint8_t etatBouton;
	uint8_t information;
} INTERFACE_BTN_BLEU;

void interface_BoutonBleuInit();

extern INTERFACE_BTN_BLEU interfaceBtnBleu;

#endif /* INC_INTERFACES_INTERFACE_BOUTONBLEU_H_ */
