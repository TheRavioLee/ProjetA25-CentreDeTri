/* serviceTriac.c */
#include "serviceTriac.h"
#include "pilote_Triac.h"

// Variables priv�es
// Variables priv�es
unsigned char serviceTriac_actif = 0;
unsigned char serviceTriac_niveau = 0;

// d�lai exprim� en TICKS de 100 �s
static unsigned int serviceTriac_delaiTicks = SERVICETRIAC_MAX_TICKS;

// gestion par demi-p�riode
static volatile unsigned char attenteDeclenchement = 0;
static volatile unsigned int  compteurTicks = 0;

extern TIM_HandleTypeDef htim2;

/**
 * @brief  Initialisation du service triac
 */
void serviceTriac_initialise(void)
{
    serviceTriac_actif = 0;
    serviceTriac_niveau = 0;
    serviceTriac_delaiTicks = SERVICETRIAC_MAX_TICKS;
    compteurTicks = 0;
    attenteDeclenchement = 0;
    piloteTriac_setCTRL();
}

/**
 * @brief  Active le contr�le du triac
 */
void serviceTriac_active(void)
{
    serviceTriac_actif = 1;
}

/**
 * @brief  D�sactive le contr�le du triac
 */
void serviceTriac_desactive(void)
{
    serviceTriac_actif = 0;
    piloteTriac_setCTRL();
    HAL_TIM_Base_Stop_IT(&htim2);
}

/**
 * @brief  Retourne l'�tat du triac
 * @retval 1 si actif, 0 si inactif
 */
unsigned char serviceTriac_estActif(void)
{
    return serviceTriac_actif;
}

/**
 * @brief  Fixe le niveau de puissance du triac
 * @param  niveau_pourcent : Niveau en % (0-100)
 */
void serviceTriac_fixeNiveau(unsigned char niveau_pourcent)
{
    if (niveau_pourcent > 100)
    {
        niveau_pourcent = 100;
    }

    serviceTriac_niveau = niveau_pourcent;

    // 0%  -> d�lai MAX (triac d�clench� tr�s tard  ? faible lumi�re)
    // 100%-> d�lai MIN (triac d�clench� tr�s t�t  ? forte lumi�re)

    unsigned int delta = (SERVICETRIAC_MAX_TICKS - SERVICETRIAC_MIN_TICKS);

    serviceTriac_delaiTicks =
        SERVICETRIAC_MAX_TICKS - ( (unsigned int)niveau_pourcent * delta / 100 );

    // s�curit�
    if (serviceTriac_delaiTicks < SERVICETRIAC_MIN_TICKS)
        serviceTriac_delaiTicks = SERVICETRIAC_MIN_TICKS;

    if (serviceTriac_delaiTicks > SERVICETRIAC_MAX_TICKS)
        serviceTriac_delaiTicks = SERVICETRIAC_MAX_TICKS;
}

/**
 * @brief  Retourne le niveau actuel
 * @retval Niveau en % (0-100)
 */
unsigned char serviceTriac_obtenirNiveau(void)
{
    return serviceTriac_niveau;
}

/**
 * @brief  Interruption TIM7 - D�clenche le triac apr�s le d�lai
 */
void serviceTriac_ITTimer7(void)
{
  if (!serviceTriac_actif)
    {
        return;
    }

    if (!attenteDeclenchement)
    {
        // Rien � faire sur cette demi-p�riode
        return;
    }

    // On avance le d�lai : +1 tick = +100 �s
    if (compteurTicks < serviceTriac_delaiTicks)
    {
        compteurTicks++;
    }

    if (compteurTicks >= serviceTriac_delaiTicks)
    {
        // On a atteint le d�lai ? pulse gate sur le triac
        attenteDeclenchement = 0;   // ne pas relancer dans la m�me demi-p�riode

        piloteTriac_resetCTRL();

        // Petite impulsion (~quelques �s ; garde �a court pour ne pas bloquer l'IT trop longtemps)
        for (volatile unsigned int i = 0; i < 2000; i++)
        {
            __NOP();  // ou rien, juste une boucle
        }

        piloteTriac_setCTRL();
    }
}

/**
 * @brief  Interruption Zero Crossing - D�tecte le passage par z�ro
 */
void serviceTriac_ITZeroCross(void)
{
  //HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // LED verte ON
   if (!serviceTriac_actif)
    {
        return;
    }

    // Nouvelle demi-p�riode : on repart de z�ro
    compteurTicks = 0;
    attenteDeclenchement = 1;
    
}
