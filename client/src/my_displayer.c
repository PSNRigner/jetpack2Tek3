/*
** my_displayer.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:58:11 2016 loic frasse-mathon
** Last update Sat Jul  9 14:38:59 2016 loic frasse-mathon
*/

#include "client.h"

void  set_window_pos(t_client *client)
{
    if (client->id == 1)
    putenv("SDL_VIDEO_WINDOW_POS=0,0");
  else
    putenv("SDL_VIDEO_WINDOW_POS=0,400");
}

int   get_nb_elem(t_client *client, char c)
{
  int   i;
  int   j;
  int   nb;

  i = 0;
  nb = 0;
  while (i < client->map->height)
  {
    j = 0;
    while (j < client->map->width)
    {
      if (client->map->data[i][j] == c)
        nb++;
      j++;
    }
    i++;
  }
  return (nb);
}

void  puts_dots(t_client *client, SDL_Surface *ecran)
{

  SDL_Rect    position;
  SDL_Surface *electric_field[get_nb_elem(client, 'e')];
  SDL_Surface *coins[get_nb_elem(client, 'c')];

  int   i;
  int   j;
  int   x;
  int   y;

  i = 0;
  x = 0;
  y = 0;
  while(i < client->map->height)
  {
    j = 0;
    while (j < client->map->width)
    {
      if (client->map->data[i][j] == 'e')
      {
        position.x = j * SIZE;
        position.y = i * SIZE;
        electric_field[x] = SDL_CreateRGBSurface(SDL_HWSURFACE, SIZE, SIZE, 32, 0, 0, 0, 0);
        SDL_FillRect(electric_field[x], NULL, SDL_MapRGB(ecran->format, 0, 100, 150));
        SDL_BlitSurface(electric_field[x], NULL, ecran, &position); 
        x++;
      }
      else if(client->map->data[i][j] == 'c')
      {
        position.x = j * SIZE;
        position.y = i * SIZE;
        coins[y] = SDL_CreateRGBSurface(SDL_HWSURFACE, SIZE, SIZE, 32, 0, 0, 0, 0);
        SDL_FillRect(coins[y], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
        SDL_BlitSurface(coins[y], NULL, ecran, &position);
        y++; 
      }
      j++;
    }
    i++;
  }
}

int		my_display(t_client *client)
{
  SDL_Surface	*ecran;

  ecran = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  set_window_pos(client);

  ecran = SDL_SetVideoMode(client->map->width * SIZE,
			   client->map->height * SIZE, 32, SDL_RESIZABLE);

  if (ecran == NULL)
      my_exit("Impossible de charger le mode vidéo", 1);
  SDL_WM_SetCaption("JetPack2Tek3", NULL);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 102));
  puts_dots(client, ecran);
  SDL_Flip(ecran);
  my_pause();
  SDL_Quit();

  return (EXIT_SUCCESS);
}

void		my_pause()
{
  int		continuer;
  SDL_Event	event;

  continuer = 1;
  while (continuer)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	continuer = 0;
    }
}
