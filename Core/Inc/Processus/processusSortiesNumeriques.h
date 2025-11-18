/*
 * processusSortiesNumeriques.h
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_PROCESSUS_PROCESSUSSORTIESNUMERIQUES_H_
#define INC_PROCESSUS_PROCESSUSSORTIESNUMERIQUES_H_


#define SORTIE1_1 ((interfacePCF8574.sortiesCarte1 >> 0) & 0x01)
#define SORTIE2_1 ((interfacePCF8574.sortiesCarte1 >> 1) & 0x01)
#define SORTIE3_1 ((interfacePCF8574.sortiesCarte1 >> 2) & 0x01)
#define SORTIE4_1 ((interfacePCF8574.sortiesCarte1 >> 3) & 0x01)
#define SORTIE5_1 ((interfacePCF8574.sortiesCarte1 >> 4) & 0x01)
#define SORTIE6_1 ((interfacePCF8574.sortiesCarte1 >> 5) & 0x01)
#define SORTIE7_1 ((interfacePCF8574.sortiesCarte1 >> 6) & 0x01)
#define SORTIE8_1 ((interfacePCF8574.sortiesCarte1 >> 7) & 0x01)

#define SORTIE1_2 ((interfacePCF8574.sortiesCarte2 >> 0) & 0x01)
#define SORTIE2_2 ((interfacePCF8574.sortiesCarte2 >> 1) & 0x01)
#define SORTIE3_2 ((interfacePCF8574.sortiesCarte2 >> 2) & 0x01)
#define SORTIE4_2 ((interfacePCF8574.sortiesCarte2 >> 3) & 0x01)
#define SORTIE5_2 ((interfacePCF8574.sortiesCarte2 >> 4) & 0x01)
#define SORTIE6_2 ((interfacePCF8574.sortiesCarte2 >> 5) & 0x01)
#define SORTIE7_2 ((interfacePCF8574.sortiesCarte2 >> 6) & 0x01)
#define SORTIE8_2 ((interfacePCF8574.sortiesCarte2 >> 7) & 0x01)


//Fonctions publiques
void processusSortiesNum_Init(void);

#endif /* INC_PROCESSUS_PROCESSUSSORTIESNUMERIQUES_H_ */
