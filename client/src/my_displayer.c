#include "client.h"

int                 my_display(t_client *client)
{
    SDL_Surface *   ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(client->map->width * 30, client->map->height * 30, 32, SDL_RESIZABLE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("JetPack2Tek3", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 102));
    SDL_Flip(ecran); /* Mise à jour de l'écran avec sa nouvelle couleur */
    my_pause();
    SDL_Quit();

    return EXIT_SUCCESS;
}
 
void                my_pause()
{
    int             continuer;
    SDL_Event       event;

    continuer = 1;
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