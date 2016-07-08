#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void pause();
 
int main(void)
{
	SDL_Surface *ecran = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(1800, 300, 32, SDL_RESIZABLE);

    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_WM_SetCaption("JetPack2Tek3", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 102));

    SDL_Flip(ecran);

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
