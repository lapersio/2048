#include "main.h"
#include <SDL.h>


bool bloque(int carte[4][4], direction sens)
{
    ///sert à vérifier si un déplacement est possible dans une direction donnée
    int i,j;
    if(sens==GAUCHE)
    {
        for(i=0;i<4;i++)
        {
            for(j=1;j<4;j++)
            {
                if(carte[i][j]!=0  && carte[i][j-1]==0)
                    return false;
            }
        }
    }
    else if(sens==DROITE)
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<3;j++)
            {
                if(carte[i][j]!=0 && carte[i][j+1]==0)
                    return false;
            }
        }
    }
    else if(sens==HAUT)
    {
        for(i=3;i>0;i--)
        {
            for(j=0;j<4;j++)
            {
                if(carte[i][j]!=0 && carte[i-1][j]==0)
                    return false;
            }
        }
    }
    else
    {
        for(i=0;i<3;i++)
        {
            for(j=0;j<4;j++)
            {
                if(carte[i][j]!=0 && carte[i+1][j]==0)
                    return false;
            }
        }
    }

    return true;
}


bool deplacement(int carte[4][4], SDL_Surface *ecran, SDL_Surface *tuiles[], int *score, direction sens)
{
    ///sert à déplacer l'ensemble des tuiles de la grilles dans le sens donné par l'utilisateur
    if(bloque(carte,sens) )
    {
        if(fusion(carte,sens,score))
        {
            miseAJour(ecran,carte,tuiles);
            miseAJourScore(ecran,*score);
            SDL_Delay(PAUSENOUVELLETUILE);
            nouvelleTuile(carte);
        }
        return false;
    }

    //Un déplacement de tuiles est possible, on les deplace selon la direction voulue

    int i,j;
    if(sens==GAUCHE)
    {
        do
        {
            for(i=0;i<4;i++)
            {
                for(j=0;j<3;j++)
                {
                    if(carte[i][j]==0 && carte[i][j+1]!=0)
                    {
                        carte[i][j]=carte[i][j+1];
                        carte[i][j+1]=0;
                    }
                }
            }
            SDL_Delay(PAUSEDEPLACEMENT);
            miseAJour(ecran,carte,tuiles);
        }while(!bloque(carte,sens));

    }
    else if(sens==DROITE)
    {
        do
        {
            for(i=0;i<4;i++)
            {
                for(j=3;j>0;j--)
                {
                    if(carte[i][j]==0 && carte[i][j-1]!=0)
                    {
                        carte[i][j]=carte[i][j-1];
                        carte[i][j-1]=0;
                    }
                }
            }
            SDL_Delay(PAUSEDEPLACEMENT);
            miseAJour(ecran,carte,tuiles);
        }while(!bloque(carte,sens));
    }
    else if(sens==HAUT)
    {
        do
        {
            for(i=0;i<3;i++)
            {
                for(j=0;j<4;j++)
                {
                    if(carte[i][j]==0 && carte[i+1][j]!=0)
                    {
                        carte[i][j]=carte[i+1][j];
                        carte[i+1][j]=0;
                    }
                }
            }
            SDL_Delay(PAUSEDEPLACEMENT);
            miseAJour(ecran,carte,tuiles);
        }while(!bloque(carte,sens));
    }
    else
    {
        do
        {
            for(i=3;i>0;i--)
            {
                for(j=0;j<4;j++)
                {
                    if(carte[i][j]==0 && carte[i-1][j]!=0)
                    {
                        carte[i][j]=carte[i-1][j];
                        carte[i-1][j]=0;
                    }
                }
            }
            SDL_Delay(PAUSEDEPLACEMENT);
            miseAJour(ecran,carte,tuiles);
        }while(!bloque(carte,BAS));
    }
    if(fusion(carte,sens,score))
        miseAJourScore(ecran,*score);
    SDL_Delay(PAUSEDEPLACEMENT);
    miseAJour(ecran,carte,tuiles);
    return true;
}

bool fusion(int carte[4][4], direction sens, int *score)
{
    ///Sert a fusionner des tuiles adjacentes selon la direction donnée par le joueur
    ///renvoie true si il y a eu fusion de tuiles, sinon renvoie false
    int i,j,k;
    bool fusionEffectuee=false;
    if(sens==GAUCHE)
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<3;j++)
            {
                if(carte[i][j]==carte[i][j+1] && carte[i][j]!=0)
                {
                    *score+=carte[i][j]*2;
                    carte[i][j]*=2;
                    k=j+1;
                    while(k<3)
                    {
                          carte[i][k]=carte[i][k+1];
                          k++;
                    }
                    carte[i][3]=0;

                    fusionEffectuee=true;

                }
            }
        }
    }
    else if(sens==DROITE)
    {
        for(i=0;i<4;i++)
        {
            for(j=3;j>0;j--)
            {
                if(carte[i][j]==carte[i][j-1] && carte[i][j]!=0)
                {
                    *score+=carte[i][j]*2;
                    carte[i][j]*=2;
                    k=j-1;
                    while(k>0)
                    {
                        carte[i][k]=carte[i][k-1];
                        k--;
                    }
                    carte[i][0]=0;
                    fusionEffectuee=true;
                }
            }
        }
    }
    else if(sens==HAUT)
    {
        for(i=0;i<3;i++)
        {
            for(j=0;j<4;j++)
            {
                if(carte[i][j]==carte[i+1][j] && carte[i][j]!=0)
                {
                    *score+=carte[i][j]*2;
                    carte[i][j]*=2;
                    k=i+1;
                    while(k<3)
                    {
                        carte[k][j]=carte[k+1][j];
                        k++;
                    }
                    carte[3][j]=0;
                    fusionEffectuee=true;
                }
            }
        }
    }
    else
    {
        for(i=3;i>0;i--)
        {
            for(j=0;j<4;j++)
            {
                if(carte[i][j]==carte[i-1][j] && carte[i][j]!=0)
                {
                    *score+=carte[i][j]*2;
                    carte[i][j]*=2;
                    k=i-1;
                    while(k>0)
                    {
                        carte[k][j]=carte[k-1][j];
                        k--;
                    }
                    carte[0][j]=0;
                    fusionEffectuee=true;
                }
            }
        }
    }
    return fusionEffectuee;
}
