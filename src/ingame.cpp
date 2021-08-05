#include <cstdio>
#include <ctime>
#include <cstring>

#include "main.h"

#include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>

int jouer(SDL_Surface *ecran)
{
    ///fonction de jeu, gère la boucle principale et les evenements comme
    /// les clics ou les touches du clavier

    //---------------------------------------------------> Variables
    //Evenement
    SDL_Event event;

    //positions
    SDL_Rect position;

    //surfaces
    SDL_Surface *arriere=IMG_Load("images/arriere_plan.png");

    //variable de base
    bool continuer=true;
    int carte[4][4];
    SDL_Surface *tuiles[18];
    int i,j;
    int score=0;
    direction sens;
    //---------------------------------------------------> Début

    //positionnement du fond
    position.x=0;
    position.y=0;
    SDL_BlitSurface(arriere,NULL,ecran,&position);
    SDL_Flip(ecran);

    //on initialise la carte et le tableau des tuiles
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            carte[i][j]=0;
    }
    initialiserTuiles(tuiles);
    srand(time(NULL));
    nouvelleTuile(carte);
    miseAJourScore(ecran,score);
    afficherRecord(ecran);
    miseAJour(ecran,carte,tuiles);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return ALTF4;
            case SDL_KEYDOWN:
            {

                switch(event.key.keysym.sym)
                {
                case SDLK_LEFT:
                {
                    sens=GAUCHE;
                    break;
                }
                case SDLK_RIGHT:
                {
                    sens=DROITE;
                    break;
                }
                case SDLK_UP:
                {
                   sens=HAUT;
                   break;
                }
                case SDLK_DOWN:
                {
                   sens=BAS;
                   break;
                }
                case SDLK_ESCAPE:
                {
                    if(afficherEcranFin(ecran,score,maximumCarte(carte))==ALTF4)
                        return ALTF4;
                    return GAMEOVER;
                    break;
                }
                default:
                {
                    sens=INCONNU; //si on appuie sur une autre touche on met le sens de déplacement à "inconnu"
                    break;
                }
                }
                if(sens!=INCONNU)
                {
                    if(deplacement(carte,ecran,tuiles,&score,sens))
                    {
                        nouvelleTuile(carte);
                        if(cartePleine(carte))
                        {
                            if(gameOver(carte))
                            {
                                miseAJour(ecran,carte,tuiles);
                                SDL_Delay(PAUSEGAMEOVER);

                                if(afficherEcranFin(ecran,score,maximumCarte(carte))==ALTF4)
                                    return ALTF4;
                                return GAMEOVER;
                            }
                        }
                    }
                    else
                    {
                        if(cartePleine(carte))
                        {
                            if(gameOver(carte))
                            {
                                miseAJour(ecran,carte,tuiles);
                                SDL_Delay(PAUSEGAMEOVER);

                                if(afficherEcranFin(ecran,score,maximumCarte(carte))==ALTF4)
                                    return ALTF4;
                                return GAMEOVER;
                            }
                        }
                    }
                }
                miseAJour(ecran,carte,tuiles);
                break;
            }
        }
    }

    for(i=0;i<18;i++)
        SDL_FreeSurface(tuiles[i]);
    SDL_FreeSurface(arriere);

    return 0;
}

void initialiserTuiles(SDL_Surface *tuiles[])
{
    ///charge les images des tuiles dans le tableau

    tuiles[0]=IMG_Load("images/tuiles/0.png");
    tuiles[1]=IMG_Load("images/tuiles/2.png");
    tuiles[2]=IMG_Load("images/tuiles/4.png");
    tuiles[3]=IMG_Load("images/tuiles/8.png");
    tuiles[4]=IMG_Load("images/tuiles/16.png");
    tuiles[5]=IMG_Load("images/tuiles/32.png");
    tuiles[6]=IMG_Load("images/tuiles/64.png");
    tuiles[7]=IMG_Load("images/tuiles/128.png");
    tuiles[8]=IMG_Load("images/tuiles/256.png");
    tuiles[9]=IMG_Load("images/tuiles/512.png");
    tuiles[10]=IMG_Load("images/tuiles/1024.png");
    tuiles[11]=IMG_Load("images/tuiles/2048.png");
    tuiles[12]=IMG_Load("images/tuiles/4096.png");
    tuiles[13]=IMG_Load("images/tuiles/8192.png");
    tuiles[14]=IMG_Load("images/tuiles/16384.png");
    tuiles[15]=IMG_Load("images/tuiles/32768.png");
    tuiles[16]=IMG_Load("images/tuiles/65536.png");
    tuiles[17]=IMG_Load("images/tuiles/131072.png");
}

int correspondant(int nombre)
{
    ///genere l'indice dans le tableau à partir du nombre sur la tuile
    int i=0;
    while(nombre>=2)
    {
        nombre/=2;
        i++;
    }
    return i;
}

void miseAJour(SDL_Surface *ecran, int carte[4][4], SDL_Surface *tuiles[])
{
    ///mets à jour l'ecran en ré-affichant les tuiles dans leur positions respectives

    SDL_Rect position;
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            position.x=j*90+215;
            position.y=i*90+115;
            SDL_BlitSurface(tuiles[correspondant(carte[i][j])],NULL,ecran,&position);
        }
    }
    SDL_Flip(ecran);
}

int hasard(int min, int max)
{
    ///génère un nombre alétoire dans l'intervalle [min,max]
    return(min + (rand()%(max-min+1)));
}

bool cartePleine(int carte[4][4])
{
    ///verifie si la grille de tuiles est pleine
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(carte[i][j]==0)
                return false;
        }
    }
    return true;
}

void nouvelleTuile(int carte[4][4])
{
    ///ajoute  une nouvelle tuile à une position aléatoire

    int i,j,k;
    i=hasard(1,10);
    //on patiente un peu avant de créer la tuile
    SDL_Delay(PAUSENOUVELLETUILE);
    //7chances sur 10 de créer une nouvelle tuile avec un 2 et 3 chances / 10 que ce soit 4
    if(i<=7) k=2;
    else k=4;
    //on prends une case vide aléatoire et on lui attribue k (la valeur de la nouvelle case)
    do
    {
        i=hasard(0,3);
        j=hasard(0,3);
    }while(carte[i][j]!=0);
    carte[i][j]=k;
}

void miseAJourScore(SDL_Surface *ecran, int score)
{
    SDL_Rect gomme; //sert à effacer le précédent score
    TTF_Font *police=TTF_OpenFont("Police/score.ttf",30);
    SDL_Color blanc;
    blanc.r=255;
    blanc.g=255;
    blanc.b=255;

    //on efface le précédent score
    gomme.x=607;
    gomme.y=252;
    gomme.h=65;
    gomme.w=184;
    SDL_FillRect(ecran,&gomme,SDL_MapRGB(ecran->format,238,194,46));

    //conversion du score en chaîne
    char score_ch[15];
    itoa(score,score_ch,10);

    //on met le score au centre de la zone
    int longueurScore=strlen(score_ch);
    gomme.x=698-(longueurScore*8);

    //Affichage du texte et mise à jour de l'écran
    SDL_BlitSurface(TTF_RenderText_Blended(police,score_ch,blanc),NULL,ecran,&gomme);
    SDL_Flip(ecran);
    TTF_CloseFont(police);
}

bool gameOver(int carte[4][4])
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(j>0)
            {
                if(carte[i][j-1]==carte[i][j])
                    return false;
            }
            if(j<3)
            {
                if(carte[i][j+1]==carte[i][j])
                    return false;
            }
            if(i>0)
            {
                if(carte[i-1][j]==carte[i][j])
                    return false;
            }
            if(i<3)
            {
                if(carte[i+1][j]==carte[i][j])
                    return false;
            }
        }
    }
    return true;
}

int afficherEcranFin(SDL_Surface *ecran, int score, int tuileMax)
{
    SDL_Surface *ecranGameOver=IMG_Load("images/fin_jeu.png");
    SDL_Rect position;
    TTF_Font *police=TTF_OpenFont("Police/score.ttf",50);
    SDL_Color couleur;
    SDL_Event event;
    int record;
    char score_ch[15],record_ch[15];
    bool continuer=true;

    sauvegarderScore(score,tuileMax);
    //affichage du fond
    position.x=0;
    position.y=0;
    SDL_BlitSurface(ecranGameOver,NULL,ecran,&position);

    //conversion du score en chaine
    itoa(score,score_ch,10);

    //affichage du texte du score
    position.x=380;
    position.y=185;
    couleur.r=64;
    couleur.b=0;
    couleur.g=0;
    SDL_BlitSurface(TTF_RenderText_Blended(police,score_ch,couleur),NULL,ecran,&position);

    //recupération du record
    FILE *fichier=fopen("scores","r");
    fscanf(fichier,"%d\n",&record);
    fclose(fichier);

    itoa(record,record_ch,10);

    //affichage du texte du record
    position.x=380;
    position.y=342;
    couleur.r=255;
    SDL_BlitSurface(TTF_RenderText_Blended(police,record_ch,couleur),NULL,ecran,&position);
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        {
            switch(event.type)
            {
            case SDL_QUIT:
            {
                SDL_FreeSurface(ecranGameOver);
                TTF_CloseFont(police);
                return ALTF4;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                    continuer=false;
                break;
            }
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                {
                    continuer=false;
                    break;
                }
                default:break;
                }
                break;
            }
            }
        }
    }


    SDL_FreeSurface(ecranGameOver);
    TTF_CloseFont(police);
    return RETOUR;
}

void afficherRecord(SDL_Surface *ecran)
{
    SDL_Rect position;
    TTF_Font *police=TTF_OpenFont("Police/score.ttf",30);

    SDL_Color blanc;
    int record;
    char record_ch[15];

    blanc.b=255;
    blanc.g=255;
    blanc.r=255;
    position.x=30;
    position.y=260;


    FILE *fichier=fopen("scores","r");
    fscanf(fichier,"%d ",&record);
    fclose(fichier);
    itoa(record,record_ch,10);

    SDL_BlitSurface(TTF_RenderText_Blended(police,record_ch,blanc),NULL,ecran,&position);
    SDL_Flip(ecran);

    TTF_CloseFont(police);
}

void sauvegarderScore(int score, int tuileMax)
{
    Record tab[6]; //contiendra les 5 meilleurs score et le score actuel
    int i;



    FILE *fichier=fopen("scores","r");
    //on rempli les 5 premiers éléments du tableau avec les précédents records
    for(i=0;i<5;i++)
        fscanf(fichier,"%d %d %d\\%d\\%d\n",&tab[i].score,&tab[i].tuileMax,&tab[i].date.jour,&tab[i].date.mois,&tab[i].date.annee);
    fclose(fichier);
                time_t secondes;
                struct tm instant;
                time(&secondes);
                instant=*localtime(&secondes);

    //le score actuel est mis comme dernier élément du tableau
    tab[5].score=score;
    tab[5].tuileMax=tuileMax;
    tab[5].date.jour=instant.tm_mday;
    tab[5].date.mois=instant.tm_mon+1;
    tab[5].date.annee=instant.tm_year+1900;

    //on trie le tableau par ordre décroissant de score
    bool echange;
    Record temp;

    do
    {
        echange=false;
        for(i=0;i<5;i++)
        {
            if(tab[i].score<tab[i+1].score)
            {
                                //Echange
                //temp <- tab[i]
                temp.score=tab[i].score;
                temp.tuileMax=tab[i].tuileMax;
                temp.date.jour=tab[i].date.jour;
                temp.date.mois=tab[i].date.mois;
                temp.date.annee=tab[i].date.annee;

                //tab[i] <- tab[i+1]
                tab[i].score=tab[i+1].score;
                tab[i].tuileMax=tab[i+1].tuileMax;
                tab[i].date.jour=tab[i+1].date.jour;
                tab[i].date.mois=tab[i+1].date.mois;
                tab[i].date.annee=tab[i+1].date.annee;

                //tab[i+1] <- temp
                tab[i+1].score=temp.score;
                tab[i+1].tuileMax=temp.tuileMax;
                tab[i+1].date.jour=temp.date.jour;
                tab[i+1].date.mois=temp.date.mois;
                tab[i+1].date.annee=temp.date.annee;

                echange=true;
            }
        }
    }while(echange==true);

    //on remet les 5 plus grands scores  dans  le fichier
    system("attrib -H scores"); //décache le fichier pour pouvoir y écrire
    fichier=fopen("scores","w+");

    for(i=0;i<5;i++)
        fprintf(fichier,"%d %d %d\\%d\\%d\n",tab[i].score,tab[i].tuileMax,tab[i].date.jour,tab[i].date.mois,tab[i].date.annee);
    fclose(fichier);
    system("attrib +H scores"); //recache le fichier
}
