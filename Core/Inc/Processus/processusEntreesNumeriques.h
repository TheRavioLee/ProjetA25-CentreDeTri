/*
 * processusEntreesNumeriques.h
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_PROCESSUS_PROCESSUSENTREESNUMERIQUES_H_
#define INC_PROCESSUS_PROCESSUSENTREESNUMERIQUES_H_

#include "interface_PCF8574.h"

#define ENTREE1_1 ((interfacePCF8574.entreesCarte1 >> 0) & 0x01)
#define ENTREE2_1 ((interfacePCF8574.entreesCarte1 >> 1) & 0x01)
#define ENTREE3_1 ((interfacePCF8574.entreesCarte1 >> 2) & 0x01)
#define ENTREE4_1 ((interfacePCF8574.entreesCarte1 >> 3) & 0x01)
#define ENTREE5_1 ((interfacePCF8574.entreesCarte1 >> 4) & 0x01)
#define ENTREE6_1 ((interfacePCF8574.entreesCarte1 >> 5) & 0x01)
#define ENTREE7_1 ((interfacePCF8574.entreesCarte1 >> 6) & 0x01)
#define ENTREE8_1 ((interfacePCF8574.entreesCarte1 >> 7) & 0x01)

#define ENTREE1_2 ((interfacePCF8574.entreesCarte2 >> 0) & 0x01)
#define ENTREE2_2 ((interfacePCF8574.entreesCarte2 >> 1) & 0x01)
#define ENTREE3_2 ((interfacePCF8574.entreesCarte2 >> 2) & 0x01)
#define ENTREE4_2 ((interfacePCF8574.entreesCarte2 >> 3) & 0x01)
#define ENTREE5_2 ((interfacePCF8574.entreesCarte2 >> 4) & 0x01)
#define ENTREE6_2 ((interfacePCF8574.entreesCarte2 >> 5) & 0x01)
#define ENTREE7_2 ((interfacePCF8574.entreesCarte2 >> 6) & 0x01)
#define ENTREE8_2 ((interfacePCF8574.entreesCarte2 >> 7) & 0x01)

#define ENTREE1_3 ((interfacePCF8574.entreesCarte3 >> 0) & 0x01)
#define ENTREE2_3 ((interfacePCF8574.entreesCarte3 >> 1) & 0x01)
#define ENTREE3_3 ((interfacePCF8574.entreesCarte3 >> 2) & 0x01)
#define ENTREE4_3 ((interfacePCF8574.entreesCarte3 >> 3) & 0x01)
#define ENTREE5_3 ((interfacePCF8574.entreesCarte3 >> 4) & 0x01)
#define ENTREE6_3 ((interfacePCF8574.entreesCarte3 >> 5) & 0x01)
#define ENTREE7_3 ((interfacePCF8574.entreesCarte3 >> 6) & 0x01)
#define ENTREE8_3 ((interfacePCF8574.entreesCarte3 >> 7) & 0x01)


//Fonctions publiques
void processusEntreesNum_Init(void);


#endif /* INC_PROCESSUS_PROCESSUSENTREESNUMERIQUES_H_ */
