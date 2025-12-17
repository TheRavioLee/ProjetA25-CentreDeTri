/* processusTriac.h */
#ifndef PROCESSUS_ASCENSEUR_H
#define PROCESSUS_SCENSEUR_H

// Configuration
#define PROCESSUSTRIAC_NIVEAU_MAX           94    // Niveau maximum (%)
#define PROCESSUSTRIAC_INCREMENT            1      // Incrément par étape (%)
#define PROCESSUSTRIAC_DELAI_MS_PAR_ETAPE   40    // Délai entre chaque changement (ms)

// Fonctions publiques
void processusTriac_initialise(void);
void processusTriac_gere(void);
void processusTriac_demarre(void);
void processusTriac_arrete(void);
unsigned char processusTriac_obtenirNiveau(void);

#endif
