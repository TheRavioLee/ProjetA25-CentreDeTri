/* serviceTriac.h */
#ifndef SERVICE_TRIAC_H
#define SERVICE_TRIAC_H

#include "stm32f4xx_hal.h"
#include "main.h"
// Configuration
#define SERVICETRIAC_ZERO_CROSS_PIN      ZERO_CROSS_Pin 
#define SERVICETRIAC_ZERO_CROSS_PORT     ZERO_CROSS_GPIO_Port

// Durée d'un tick de TIM7 (en µs)
#define SERVICETRIAC_TICK_US              100

// Demi-période secteur 60 Hz ˜ 8333 µs
#define SERVICETRIAC_HALF_PERIOD_US       8333

// Nombre max de ticks de 100µs dans une demi-période (~83)
#define SERVICETRIAC_HALF_PERIOD_TICKS    (SERVICETRIAC_HALF_PERIOD_US / SERVICETRIAC_TICK_US)  // 83

// Limites pour notre délai en ticks
#define SERVICETRIAC_MIN_TICKS            1        // 1 * 100µs = 100µs, très tôt ? fort
#define SERVICETRIAC_MAX_TICKS            80       // 80 * 100µs = 8000µs, très tard ? faible

// Fonctions publiques
void serviceTriac_initialise(void);
void serviceTriac_fixeNiveau(unsigned char niveau_pourcent);
unsigned char serviceTriac_obtenirNiveau(void);
void serviceTriac_active(void);
void serviceTriac_desactive(void);
unsigned char serviceTriac_estActif(void);
void serviceTriac_ITTimer7(void);
void serviceTriac_ITZeroCross(void);

#endif
