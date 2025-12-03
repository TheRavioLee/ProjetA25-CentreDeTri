/*
 * processusSortiesNumeriques.h
 *
 *  Created on: Nov 13, 2025
 *      Author: thomaslajoie
 */

#ifndef INC_PROCESSUS_PROCESSUSSORTIESNUMERIQUES_H_
#define INC_PROCESSUS_PROCESSUSSORTIESNUMERIQUES_H_


//define macros pour ecriture individuelle sorties
#define CLEAR_SORTIE(var, bit)     ((var) |=  (1 << (bit)))
#define SET_SORTIE(var, bit)   ((var) &= ~(1 << (bit)))
#define TOGGLE_BIT(var, bit)  ((var) ^=  (1 << (bit)))

//******************** CARTE 1

#define SET_LUMIERE_VERTE()	SET_SORTIE(interfacePCF8574.sortiesCarte1, 0)
#define CLEAR_LUMIERE_VERTE() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 0)

#define SET_VENTOUSE_BAS_SOLE704() SET_SORTIE(interfacePCF8574.sortiesCarte1, 1)
#define CLEAR_VENTOUSE_BAS_SOLE704() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 1)

#define SET_VENTOUSE_HAUT_SOLE707() SET_SORTIE(interfacePCF8574.sortiesCarte1, 2)
#define CLEAR_VENTOUSE_HAUT_SOLE707() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 2)

#define SET_VACCUM_SOLE710() SET_SORTIE(interfacePCF8574.sortiesCarte1, 3)
#define CLEAR_VACCUM_SOLE710() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 3)

#define SET_ELEV_BAS_SOLE713() SET_SORTIE(interfacePCF8574.sortiesCarte1, 4)
#define CLEAR_ELEV_BAS_SOLE713() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 4)

#define SET_ELEV_HAUT_SOLE716() SET_SORTIE(interfacePCF8574.sortiesCarte1, 5)
#define CLEAR_ELEV_HAUT_SOLE716() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 5)

#define SET_EJECT_POS_ENTREE_SOLE719() SET_SORTIE(interfacePCF8574.sortiesCarte1, 6)
#define CLEAR_EJECT_POS_ENTREE_SOLE719() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 6)

#define SET_EJECT_POS_SORTIE_SOLE722() SET_SORTIE(interfacePCF8574.sortiesCarte1, 7)
#define CLEAR_EJECT_POS_SORTIE_SOLE722() CLEAR_SORTIE(interfacePCF8574.sortiesCarte1, 7)

//********************* CARTE 2

#define SET_POUSSOIR_POS_SORTIE_SOLE725() SET_SORTIE(interfacePCF8574.sortiesCarte2, 0)
#define CLEAR_POUSSOIR_POS_SORTIE_SOLE725() CLEAR_SORTIE(interfacePCF8574.sortiesCarte2, 0)

#define SET_RELAIS_MOTEUR_CONVOYEUR() SET_SORTIE(interfacePCF8574.sortiesCarte2, 1)
#define CLEAR_RELAIS_MOTEUR_CONVOYEUR() CLEAR_SORTIE(interfacePCF8574.sortiesCarte2, 1)

#define SET_CONTROLLER_RELEASE() SET_SORTIE(interfacePCF8574.sortiesCarte2, 3)
#define CLEAR_CONTROLLER_RELEASE() CLEAR_SORTIE(interfacePCF8574.sortiesCarte2, 3)

#define SET_SELECT_POS_0() SET_SORTIE(interfacePCF8574.sortiesCarte2, 4)
#define CLEAR_SELECT_POS_0() CLEAR_SORTIE(interfacePCF8574.sortiesCarte2, 4)

#define SET_SELECT_POS_1() SET_SORTIE(interfacePCF8574.sortiesCarte2, 5)
#define CLEAR_SELECT_POS_1() CLEAR_SORTIE(interfacePCF8574.sortiesCarte2, 5)

#define SET_SELECT_POS_2() SET_SORTIE(interfacePCF8574.sortiesCarte2, 6)
#define CLEAR_SELECT_POS_2() CLEAR_SORTIE(interfacePCF8574.sortiesCarte2, 6)

#define SET_START_POS_PROCESS() SET_SORTIE(interfacePCF8574.sortiesCarte2, 7)
#define CLEAR_START_POS_PROCESS() CLEAR_SORTIE(interfacePCF8574.sortiesCarte2, 7)


//define pour lecture individuelles sorties
#define LUMIERE_VERTE ((interfacePCF8574.sortiesCarte1 >> 0) & 0x01)
#define VENTOUSE_BAS_SOLE704 ((interfacePCF8574.sortiesCarte1 >> 1) & 0x01)
#define VENTOUSE_HAUT_SOLE707 ((interfacePCF8574.sortiesCarte1 >> 2) & 0x01)
#define VACCUM_SOLE710 ((interfacePCF8574.sortiesCarte1 >> 3) & 0x01)
#define ELEV_BAS_SOLE713 ((interfacePCF8574.sortiesCarte1 >> 4) & 0x01)
#define ELEV_HAUT_SOLE716 ((interfacePCF8574.sortiesCarte1 >> 5) & 0x01)
#define POUSSOIR_POS_ENTREE_SOLE719 ((interfacePCF8574.sortiesCarte1 >> 6) & 0x01)
#define POUSSOIR_POS_SORTIE_SOLE722 ((interfacePCF8574.sortiesCarte1 >> 7) & 0x01)

#define EJECT_POS_SORTIE_SOLE725 ((interfacePCF8574.sortiesCarte2 >> 0) & 0x01)
#define RELAIS_MOTEUR_CONVOYEUR ((interfacePCF8574.sortiesCarte2 >> 1) & 0x01)
#define SORTIE3_2 ((interfacePCF8574.sortiesCarte2 >> 2) & 0x01)
#define CONTROLLER_RELEASE ((interfacePCF8574.sortiesCarte2 >> 3) & 0x01)
#define SELECT_POS_0 ((interfacePCF8574.sortiesCarte2 >> 4) & 0x01)
#define SELECT_POS_1 ((interfacePCF8574.sortiesCarte2 >> 5) & 0x01)
#define SELECT_POS_2 ((interfacePCF8574.sortiesCarte2 >> 6) & 0x01)
#define START_POS_PROCESS ((interfacePCF8574.sortiesCarte2 >> 7) & 0x01)


//Fonctions publiques
void processusSortiesNum_Init(void);

#endif /* INC_PROCESSUS_PROCESSUSSORTIESNUMERIQUES_H_ */
