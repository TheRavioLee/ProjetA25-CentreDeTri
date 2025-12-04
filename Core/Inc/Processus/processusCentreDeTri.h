/*
 * processusCentreDeTri.h
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_PROCESSUS_PROCESSUSCENTREDETRI_H_
#define INC_PROCESSUS_PROCESSUSCENTREDETRI_H_

void processusCentreDeTri_Init(void);

typedef struct {
	uint8_t mode;
	uint8_t requete;
	uint8_t information;
	uint8_t couleurBloc;

}CENTRE_DE_TRI;

extern CENTRE_DE_TRI centreDeTri;

#endif /* INC_PROCESSUS_PROCESSUSCENTREDETRI_H_ */
