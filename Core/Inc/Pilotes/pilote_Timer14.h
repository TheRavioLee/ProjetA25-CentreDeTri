/*
 * pilote_Timer14_1ms.h
 *
 *  Created on: May 21, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_PILOTE_TIMER14_H_
#define INC_PILOTE_TIMER14_H_


//Fonctions publiques:
void piloteTimer14_initialise(void);
void piloteTimer14_permetLesInterruptions(void);

//Variables publiques:
extern void (*piloteTimer14_execute)(void);

#endif /* INC_PILOTE_TIMER14_H_ */
