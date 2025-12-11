/*
 * interface_Moteur.h
 *
 *  Created on: Nov 19, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_INTERFACES_INTERFACE_MOTEUR_H_
#define INC_INTERFACES_INTERFACE_MOTEUR_H_

#define STEPS_PAR_REV 100
#define VITESSE_RAPIDE 3
#define VITESSE_LENT 10
#define MONTER -1
#define DESCENDRE 1

typedef struct{
	int8_t directionMoteur;
	uint8_t vitesseMoteur;
	uint8_t requete;
} INTERFACE_MOTEUR;

extern INTERFACE_MOTEUR interfaceMoteur;

void interfaceMoteur_Init(void);

#endif /* INC_INTERFACES_INTERFACE_MOTEUR_H_ */
