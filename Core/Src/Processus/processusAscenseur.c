/* processusTriac.c */
#include "main.h"
#include "processusAscenseur.h"
#include "serviceTriac.h"
#include "serviceBaseTemps.h"

// Variables priv�es
static unsigned char processusTriac_niveau = 0;
static unsigned char processusTriac_montee = 1;  // 1 = mont�e, 0 = descente
static unsigned char processusTriac_actif = 0;

/**
 * @brief  Initialisation du processus triac
 */
void processusTriac_initialise(void)
{
    processusTriac_niveau = 0;
    processusTriac_montee = 1;
    processusTriac_actif = 0;
    
    serviceTriac_fixeNiveau(0);
    processusTriac_demarre();
    serviceBaseDeTemps_execute[TRIAC_PHASE] = processusTriac_gere;
}

/**
 * @brief  D�marre le processus
 */
void processusTriac_demarre(void)
{
    processusTriac_actif = 1;
    serviceTriac_active();
}

/**
 * @brief  Arr�te le processus
 */
void processusTriac_arrete(void)
{
    processusTriac_actif = 0;
    serviceTriac_desactive();
}

/**
 * @brief  Retourne le niveau actuel
 * @retval Niveau en % (0-100)
 */
unsigned char processusTriac_obtenirNiveau(void)
{
    return processusTriac_niveau;
}

/**
 * @brief  Gestion du processus - Appel� p�riodiquement par serviceBaseDeTemps
 *         Incr�mente/d�cr�mente progressivement le niveau (mont�e/descente)
 */
void processusTriac_gere(void)
{
    static unsigned int compteurMs = 0;
    
    if (!processusTriac_actif)
    {
        return;
    }
    
    // Timer6Up � 2000Hz = appel� toutes les 0.5ms
    // Compteur pour atteindre le d�lai souhait�
    if (++compteurMs < (PROCESSUSTRIAC_DELAI_MS_PAR_ETAPE * 2))
    {
        return;
    }
    compteurMs = 0;
    
    // Mont�e ou descente
    if (processusTriac_montee)
    {
        // Phase de mont�e
        if (processusTriac_niveau < PROCESSUSTRIAC_NIVEAU_MAX)
        {
            processusTriac_niveau += PROCESSUSTRIAC_INCREMENT;
            if (processusTriac_niveau > PROCESSUSTRIAC_NIVEAU_MAX)
            {
                processusTriac_niveau = PROCESSUSTRIAC_NIVEAU_MAX;
            }
        }
        else
        {
            // Atteint le max, passer en descente
            processusTriac_montee = 0;
        }
    }
    else
    {
        // Phase de descente
        if (processusTriac_niveau > 0)
        {
            if (processusTriac_niveau >= PROCESSUSTRIAC_INCREMENT)
            {
                processusTriac_niveau -= PROCESSUSTRIAC_INCREMENT;
            }
            else
            {
                processusTriac_niveau = 0;
            }
        }
        else
        {
            // Atteint le min, repasser en mont�e
            processusTriac_montee = 1;
        }
    }
    
    // Appliquer le nouveau niveau
    serviceTriac_fixeNiveau(processusTriac_niveau);
}
