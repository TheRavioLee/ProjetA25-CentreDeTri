/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TRIAC_CTRL_Pin GPIO_PIN_6
#define TRIAC_CTRL_GPIO_Port GPIOE
#define TRIAC_EXTI_Pin GPIO_PIN_13
#define TRIAC_EXTI_GPIO_Port GPIOC
#define TRIAC_EXTI_EXTI_IRQn EXTI15_10_IRQn
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define BTN_BLEU_Pin GPIO_PIN_0
#define BTN_BLEU_GPIO_Port GPIOA
#define PHASE_4_Pin GPIO_PIN_5
#define PHASE_4_GPIO_Port GPIOA
#define PHASE_2_Pin GPIO_PIN_6
#define PHASE_2_GPIO_Port GPIOA
#define PHASE_3_Pin GPIO_PIN_7
#define PHASE_3_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_0
#define RD_GPIO_Port GPIOB
#define A4_Pin GPIO_PIN_1
#define A4_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define D0_Pin GPIO_PIN_8
#define D0_GPIO_Port GPIOE
#define D1_Pin GPIO_PIN_9
#define D1_GPIO_Port GPIOE
#define D2_Pin GPIO_PIN_10
#define D2_GPIO_Port GPIOE
#define D3_Pin GPIO_PIN_11
#define D3_GPIO_Port GPIOE
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOE
#define D5_Pin GPIO_PIN_13
#define D5_GPIO_Port GPIOE
#define D6_Pin GPIO_PIN_14
#define D6_GPIO_Port GPIOE
#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOE
#define CS0_Pin GPIO_PIN_11
#define CS0_GPIO_Port GPIOB
#define CS1_Pin GPIO_PIN_12
#define CS1_GPIO_Port GPIOB
#define CS2_Pin GPIO_PIN_13
#define CS2_GPIO_Port GPIOB
#define CS3_Pin GPIO_PIN_14
#define CS3_GPIO_Port GPIOB
#define A0_Pin GPIO_PIN_8
#define A0_GPIO_Port GPIOD
#define A1_Pin GPIO_PIN_9
#define A1_GPIO_Port GPIOD
#define A2_Pin GPIO_PIN_10
#define A2_GPIO_Port GPIOD
#define A3_Pin GPIO_PIN_11
#define A3_GPIO_Port GPIOD
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define OTG_FS_OverCurrent_Pin GPIO_PIN_5
#define OTG_FS_OverCurrent_GPIO_Port GPIOD
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOB
#define PHASE_1_Pin GPIO_PIN_0
#define PHASE_1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
#define FREQ_BASETEMPS_HZ 1000
#define FREQ_LECTURE_BTN_HZ 100

//Definitions Base de temps
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 4
#define ENTREES_NUM_PHASE 0
//#define ENTREE_ANALOGUE_PHASE 1
#define SORTIES_NUM_PHASE 1
#define INTERFACE_BTN_BLEU_PHASE 2
#define PROCESSUS_AFFICHAGE_PHASE 3

//#define CENTRE_DE_TRI_PHASE 4

#define INFORMATION_DISPONIBLE 1
#define INFORMATION_TRAITEE 0
#define REQUETE_ACTIVE 1
#define REQUETE_TRAITEE 0
#define READ_GOOD 1
#define READ_FAIL 0
#define WRITE_GOOD 1
#define WRITE_FAIL 0

//Fonctions publiques
void doNothing(void);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
