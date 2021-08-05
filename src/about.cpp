#include "main.h"

#include <SDL.h>
    #include <SDL_image.h>

int aPropos(SDL_Surface *ecran)
{
    //-----------------------------------------------------------Variables
    SDL_Surface *fond=IMG_Load("images/aide.png");
    SDL_Rect position;
    SDL_Event event;

    bool continuer=true;
    //-----------------------------------------------------------Début

    //placement du fond
    position.x=0;
    position.y=0;
    SDL_BlitSurface(fond,NULL,ecran, &position);
    SDL_Flip(ecran);
    SDL_Delay(100);
      while(continuer)
      {
          SDL_WaitEvent(&event);
          switch(event.type)
          {
                case SDL_QUIT:
                {
                    SDL_FreeSurface(fond);
                    return ALTF4;
                }
                case SDL_KEYDOWN:
                {
                     if(event.key.keysym.sym==SDLK_ESCAPE)
                         continuer=false;
                     break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    if(event.button.button==SDL_BUTTON_LEFT)
                        continuer=false;
                    break;
                }
                default:break;
          }
      }
    SDL_FreeSurface(fond);
    return RETOUR;
}
