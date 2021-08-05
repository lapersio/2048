#include <cstdlib>
#include <cstdio>

#include "main.h"

#include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>








int WinMain()
{
    ///fonction pricipale du jeu, remplaçante de int main(int argc,char **argv)

    //------------------------------------------------------->variables
    //surfaces
    SDL_Surface
            *IMG_logo=IMG_Load("images/logo.png"),
            *IMG_nouvellePartie=IMG_Load("images/nouvelle_partie.png"),
            *IMG_records=IMG_Load("images/records.png"),
            *IMG_aPropos=IMG_Load("images/a_propos.png");

    //position
    SDL_Rect position;

    //événement
    SDL_Event event;

    //variable de base
    bool continuer=true;


    //------------------------------------------------------->debut
     SDL_Init(SDL_INIT_VIDEO);
     TTF_Init();
    SDL_WM_SetCaption("2048 par Lapersio",NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("images/icone.bmp"),NULL);
    SDL_Surface *ecran=SDL_SetVideoMode(LARGEURFENETRE,HAUTEURFENETRE,
                                        32, SDL_HWSURFACE| SDL_DOUBLEBUF);


    verifierFichier(); //vérifie la présence du fichier de sauvegarde des scores
    creerMenu( ecran, IMG_logo, IMG_nouvellePartie,IMG_records, IMG_aPropos);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
              continuer=false;
            case SDL_MOUSEBUTTONDOWN: //clic
            {
                if(event.button.button==SDL_BUTTON_LEFT)//clic gauche
                {
                    if(estEntre(event.button.x,event.button.y,50,750,200,300))
                    {
                        //nouvelle partie
                           //changement momentanné du bouton
                        IMG_nouvellePartie=IMG_Load("images/nouvelle_partie2.png");
                        position.x=50;
                        position.y=200;
                        SDL_BlitSurface(IMG_nouvellePartie,NULL,ecran,&position);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        IMG_nouvellePartie=IMG_Load("images/nouvelle_partie.png");
                        SDL_BlitSurface(IMG_nouvellePartie,NULL,ecran,&position);
                        //lancement de la fonction de jeu
                        if(jouer(ecran)==ALTF4)
                            continuer=false ;
                        else
                            creerMenu(ecran,IMG_logo,IMG_nouvellePartie,IMG_records,IMG_aPropos);
                    }
                    else if(estEntre(event.button.x,event.button.y,200,600,330,430))
                    {
                        //Records
                            //changement momentanné du bouton
                        IMG_records=IMG_Load("images/records2.png");
                        position.x=200;
                        position.y=330;
                        SDL_BlitSurface(IMG_records,NULL,ecran,&position);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        IMG_records=IMG_Load("images/records.png");
                        SDL_BlitSurface(IMG_records,NULL,ecran,&position);

                        if(afficherEcranStat(ecran)==ALTF4)
                            continuer=false;
                        else
                            creerMenu(ecran,IMG_logo,IMG_nouvellePartie,IMG_records,IMG_aPropos);
                    }
                    else if(estEntre(event.button.x,event.button.y,210,590,460,560))
                    {
                        //a propos
                            //changement momentanné du bouton
                        IMG_aPropos=IMG_Load("images/a_propos2.png");
                        position.x=210;
                        position.y=460;
                        SDL_BlitSurface(IMG_aPropos,NULL,ecran,&position);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        IMG_aPropos=IMG_Load("images/a_propos.png");
                        SDL_BlitSurface(IMG_aPropos,NULL,ecran,&position);

                        if(aPropos(ecran)==ALTF4)
                            continuer=false;
                        else
                            creerMenu(ecran,IMG_logo,IMG_nouvellePartie,IMG_records,IMG_aPropos);
                     }
                    SDL_Flip(ecran);
                }
            }
        }
    }

    //libération de la mémoire
    SDL_FreeSurface(IMG_aPropos);
    SDL_FreeSurface(IMG_logo);
    SDL_FreeSurface(IMG_nouvellePartie);
    SDL_FreeSurface(IMG_records);

    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}

bool estEntre(Uint16 x,Uint16 y,int a,int b,int c,int d)
{
    return((x>=a && x <=b ) && (y>=c && y<=d));
}

void creerMenu(SDL_Surface *ecran, SDL_Surface *IMG_logo, SDL_Surface *IMG_nouvellePartie,
               SDL_Surface *IMG_records, SDL_Surface *IMG_aPropos)
{
    ///crée le menu pricipal

    SDL_Rect position;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));  //fond en blanc


                                                //placement des images
    //logo
    position.x=0;
    position.y=0;
    SDL_BlitSurface(IMG_logo,NULL,ecran,&position);

    //nouvelle partie
    position.x=50;
    position.y=200;
    SDL_BlitSurface(IMG_nouvellePartie,NULL,ecran,&position);

    //record
    position.x=200;
    position.y=330;
    SDL_BlitSurface(IMG_records,NULL,ecran,&position);

    //A propos
    position.x=210;
    position.y=460;
    SDL_BlitSurface(IMG_aPropos,NULL,ecran,&position);

    SDL_Flip(ecran);
}

void verifierFichier(void)
{//vérifie la présence du fichier des scores
    int i;
    FILE *fichier=fopen("scores","r");
    if(!fichier)
    {
        fclose(fichier);
        fichier=fopen("scores","w");
        for(i=0;i<5;i++)
            fprintf(fichier,"0 0 0\\0\\0\n");
        fclose(fichier);
        system("attrib +H scores"); //cache le fichier des scores, bonjour la sécurité :p
    }
    else
        fclose(fichier);
}
