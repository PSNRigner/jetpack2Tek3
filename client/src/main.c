#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void pause();
 
int main(void)
{
	SDL_Surface *ecran = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(1800, 300, 32, SDL_RESIZABLE); // On tente d'ouvrir une fenêtre

    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_WM_SetCaption("JetPack2Tek3", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 102));

    SDL_Flip(ecran); /* Mise à jour de l'écran avec sa nouvelle couleur */

    pause();

    SDL_Quit();

    return EXIT_SUCCESS;
}
 
void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
