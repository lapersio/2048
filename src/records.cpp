#include "main.h"

#include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>

int afficherEcranStat(SDL_Surface *ecran)
{
    SDL_Surface *fond=IMG_Load("images/stats.png");
    SDL_Rect position;
    TTF_Font *police=TTF_OpenFont("Police/score.ttf",30);
    SDL_Color blanc;
    SDL_Event event;

    int i;
    char score[15],tuileMax[15],date[15];
    bool continuer=true;
    //--------------------------------------------------------------> Début
    position.x=0;
    position.y=0;
    SDL_BlitSurface(fond,NULL,ecran,&position);

    blanc.r=255;
    blanc.g=255;
    blanc.b=255;

    FILE *fichier=fopen("scores","r");


    for(i=0;i<5;i++)
    {
        fscanf(fichier,"%s %s %s\n",score,tuileMax,date);
        position.y=221 + (80*i);

        position.x=10;
        SDL_BlitSurface(TTF_RenderText_Blended(police,score,blanc),NULL,ecran,&position);

        position.x=225;
        SDL_BlitSurface(TTF_RenderText_Blended(police,tuileMax,blanc),NULL,ecran,&position);

        position.x=500;
        SDL_BlitSurface(TTF_RenderText_Blended(police,date,blanc),NULL,ecran,&position);
    }



    fclose(fichier);
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
        {
            SDL_FreeSurface(fond);
            TTF_CloseFont(police);
            return ALTF4;
            break;
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



    SDL_FreeSurface(fond);
    TTF_CloseFont(police);
    return RETOUR;
}

int maximumCarte(int carte[4][4])
{
    int i,j,max=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(carte[i][j]>max)
                max=carte[i][j];
        }
    }
    return max;
}
