//******************************************************************************
//   Nom du fichier : IO_BUS.h
//   Auteur : Alain Champagne                  
//      Date de cr�ation : 21-12-2015 
//        Fichier de d�claration et de d�finition des fonctions de controle des 
//        �l�ments d'entr�es sorties.
//  
//******************************************************************************
#ifndef INC_IO_BUS_H_
#define INC_IO_BUS_H_

//Include
#include "main.h"
#include "stm32f4xx_hal.h"                       //D�finition pour le KIT ARM

//Define
#define CS0 0
#define CS1 1
#define CS2 2
#define CS3 3
#define Level_CS0 1
#define Level_CS1 0
#define Level_CS2 0
#define Level_CS3 0

//Predeclaration des fonctions
 void vDelai_IO(uint8_t i);
 void vData_IN(void);
 void vData_OUT(void);
 uint8_t ucReadIO (uint8_t CSx, uint8_t Level, uint8_t ucAdresse);
 void vWriteIO(uint8_t ucEcrireDataIO, uint8_t CSx, uint8_t Level, uint8_t ucAdresse);



#endif
