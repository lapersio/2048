#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>

//Constantes
#define LARGEURFENETRE 800
#define HAUTEURFENETRE 600

#define PAUSEDEPLACEMENT 35
#define PAUSENOUVELLETUILE 150
#define PAUSEGAMEOVER 1200



//types

typedef struct Date Date;
struct Date
{
    int jour;
    int mois;
    int annee;
};

typedef struct Record Record;
struct Record
{
    int score;
    int tuileMax;
    Date date;
};

//Enumérations
enum  direction {HAUT,BAS,GAUCHE,DROITE,INCONNU};
enum fin{ALTF4,GAMEOVER,RETOUR};


//Entêtes
bool estEntre(Uint16 x,Uint16 y,int a,int b,int c,int d);
void creerMenu(SDL_Surface *ecran,SDL_Surface *IMG_logo,SDL_Surface *IMG_nouvellePartie,
               SDL_Surface *IMG_records,SDL_Surface *IMG_aPropos);

void verifierFichier(void);

int jouer(SDL_Surface *ecran);
    void afficherRecord(SDL_Surface *ecran);
    void miseAJour(SDL_Surface *ecran, int carte[4][4],SDL_Surface *tuiles[]);
    void miseAJourScore(SDL_Surface *ecran, int score);
    void initialiserTuiles(SDL_Surface *tuiles[]);
    int correspondant(int nombre);
    int hasard(int min,int max);
    bool cartePleine(int carte[4][4]);
    void nouvelleTuile(int carte[4][4]);
    bool gameOver(int carte[4][4]);
    int afficherEcranFin(SDL_Surface *ecran,int score,int tuileMax);
    void sauvegarderScore(int score,int tuileMax);
    bool deplacement(int carte[4][4], SDL_Surface *ecran, SDL_Surface *tuiles[],int *score,direction sens);
        bool bloque(int carte[4][4], direction sens);
        bool fusion(int carte[4][4],direction sens,int *score);

int aPropos(SDL_Surface *ecran);
int afficherEcranStat(SDL_Surface *ecran);
    int maximumCarte(int carte[4][4]);

#endif // MAIN_H
