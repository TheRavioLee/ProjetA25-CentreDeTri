/*
 * ServiceBaseTemps_1ms.h
 *
 *  Created on: May 21, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_SERVICEBASETEMPS_H_
#define INC_SERVICEBASETEMPS_H_

#include "main.h"


void serviceBaseDeTemps_initialise(void);

//Variables publiques:
extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

#endif /* INC_SERVICEBASETEMPS_H_ */
