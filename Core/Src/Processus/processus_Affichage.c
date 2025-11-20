/*
 * processus_Affichage.c
 *
 *  Created on: Oct 29, 2025
 *      Author: thomaslajoie
 */
#include "main.h"
#include "GLcd.h"
#include "processus_Affichage.h"
#include "ServiceBaseTemps.h"
#include "processusSortiesNumeriques.h"
#include "processusEntreesNumeriques.h"
#include "interface_ADC.h"
#include "interface_BoutonBleu.h"
#include "interface_Moteur.h"

uint8_t base_affichage[8][23] = {
		{"OUT: 1,2 | IN 3,4,5  "},
		{"1    XXXX   XXXX     "},
		{"2    XXXX   XXXX     "},
		{"3    XXXX   XXXX     "},
		{"4    XXXX   XXXX     "},
		{"5    XXXX   XXXX     "},
		{"BTN BLEU:            "},
		{"ADC: 0x              "}
};


uint16_t compteurAffichage;

void byteToBinary(uint8_t value, uint8_t *dest);
void processusAffichage_Afficher(void);
void uint16ToHex(uint16_t value, uint8_t *dest);


void uint16ToHex(uint16_t value, uint8_t *dest)
{
    const char hex[] = "0123456789ABCDEF";
    dest[0] = hex[(value >> 12) & 0x0F];
    dest[1] = hex[(value >> 8)  & 0x0F];
    dest[2] = hex[(value >> 4)  & 0x0F];
    dest[3] = hex[value & 0x0F];
}

void byteToBinary(uint8_t value, uint8_t *dest)
{
    for (int i = 0; i < 8; i++)
    {
        dest[i] = (value & (1 << (7 - i))) ? '1' : '0';
    }
}


void processusAffichage_Afficher(void)
{
	uint8_t entrees_Num1[8];
	uint8_t entrees_Num2[8];
	uint8_t entrees_Num3[8];

	uint8_t sorties_Num1[8];
	uint8_t sorties_Num2[8];

	uint8_t entree_ADC[4];
	uint8_t boutonBleu = 'X';

	if(interfaceBtnBleu.information == INFORMATION_DISPONIBLE)
	{
		interfaceBtnBleu.information = INFORMATION_TRAITEE;

		if(interfaceBtnBleu.etatBouton == BOUTON_APPUYE)
		{
			switch (interfaceMoteur.directionMoteur)
			{
			case MONTER:
				interfaceMoteur.directionMoteur = DESCENDRE;
				break;
			case DESCENDRE:
				interfaceMoteur.directionMoteur = MONTER;
				break;
			}
			boutonBleu = '1';
		}
		else
		{
			boutonBleu = '0';
		}

		vPutCharGLcd(boutonBleu, 6, 12, 5);
	}

	byteToBinary(interfacePCF8574.entreesCarte1, entrees_Num1);
	byteToBinary(interfacePCF8574.entreesCarte2, entrees_Num2);
	byteToBinary(interfacePCF8574.entreesCarte3, entrees_Num3);
	byteToBinary(interfacePCF8574.sortiesCarte1, sorties_Num1);
	byteToBinary(interfacePCF8574.sortiesCarte2, sorties_Num2);

	uint16ToHex(interfaceADC.valeurADC, entree_ADC);

	vPutCharGLcd(sorties_Num1[0], 1, 5, 5);
	vPutCharGLcd(sorties_Num1[1], 1, 6, 5);
	vPutCharGLcd(sorties_Num1[2], 1, 7, 5);
	vPutCharGLcd(sorties_Num1[3], 1, 8, 5);
	vPutCharGLcd(sorties_Num1[4], 1, 12, 5);
	vPutCharGLcd(sorties_Num1[5], 1, 13, 5);
	vPutCharGLcd(sorties_Num1[6], 1, 14, 5);
	vPutCharGLcd(sorties_Num1[7], 1, 15, 5);

	vPutCharGLcd(sorties_Num2[0], 2, 5, 5);
	vPutCharGLcd(sorties_Num2[1], 2, 6, 5);
	vPutCharGLcd(sorties_Num2[2], 2, 7, 5);
	vPutCharGLcd(sorties_Num2[3], 2, 8, 5);
	vPutCharGLcd(sorties_Num2[4], 2, 12, 5);
	vPutCharGLcd(sorties_Num2[5], 2, 13, 5);
	vPutCharGLcd(sorties_Num2[6], 2, 14, 5);
	vPutCharGLcd(sorties_Num2[7], 2, 15, 5);

	vPutCharGLcd(entrees_Num1[0], 3, 5, 5);
	vPutCharGLcd(entrees_Num1[1], 3, 6, 5);
	vPutCharGLcd(entrees_Num1[2], 3, 7, 5);
	vPutCharGLcd(entrees_Num1[3], 3, 8, 5);
	vPutCharGLcd(entrees_Num1[4], 3, 12, 5);
	vPutCharGLcd(entrees_Num1[5], 3, 13, 5);
	vPutCharGLcd(entrees_Num1[6], 3, 14, 5);
	vPutCharGLcd(entrees_Num1[7], 3, 15, 5);

	vPutCharGLcd(entrees_Num2[0], 4, 5, 5);
	vPutCharGLcd(entrees_Num2[1], 4, 6, 5);
	vPutCharGLcd(entrees_Num2[2], 4, 7, 5);
	vPutCharGLcd(entrees_Num2[3], 4, 8, 5);
	vPutCharGLcd(entrees_Num2[4], 4, 12, 5);
	vPutCharGLcd(entrees_Num2[5], 4, 13, 5);
	vPutCharGLcd(entrees_Num2[6], 4, 14, 5);
	vPutCharGLcd(entrees_Num2[7], 4, 15, 5);

	vPutCharGLcd(entrees_Num3[0], 5, 5, 5);
	vPutCharGLcd(entrees_Num3[1], 5, 6, 5);
	vPutCharGLcd(entrees_Num3[2], 5, 7, 5);
	vPutCharGLcd(entrees_Num3[3], 5, 8, 5);
	vPutCharGLcd(entrees_Num3[4], 5, 12, 5);
	vPutCharGLcd(entrees_Num3[5], 5, 13, 5);
	vPutCharGLcd(entrees_Num3[6], 5, 14, 5);
	vPutCharGLcd(entrees_Num3[7], 5, 15, 5);

	vPutCharGLcd(entree_ADC[0], 7, 7, 5);
	vPutCharGLcd(entree_ADC[1], 7, 8, 5);
	vPutCharGLcd(entree_ADC[2], 7, 9, 5);
	vPutCharGLcd(entree_ADC[3], 7, 10, 5);
}


AFFICHAGE affichageLCD;

void processusAffichageInit(void)
{
  HAL_GPIO_WritePin(GPIOB, CS0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, CS1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, CS2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, CS3_Pin, GPIO_PIN_SET);

  HAL_Delay(100);
  vInitGLcd();
  HAL_Delay(100);
  vClearGLcd(0x00);

  vPutStringGLcd(base_affichage[0], 0, 5);
  vPutStringGLcd(base_affichage[1], 1, 5);
  vPutStringGLcd(base_affichage[2], 2, 5);
  vPutStringGLcd(base_affichage[3], 3, 5);
  vPutStringGLcd(base_affichage[4], 4, 5);
  vPutStringGLcd(base_affichage[5], 5, 5);
  vPutStringGLcd(base_affichage[6], 6, 5);
  vPutStringGLcd(base_affichage[7], 7, 5);

  serviceBaseDeTemps_execute[PROCESSUS_AFFICHAGE_PHASE] =
      processusAffichage_Afficher;
}
