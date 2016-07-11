/*
** my_displayer.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:58:11 2016 loic frasse-mathon
** Last update Mon Jul 11 11:16:58 2016 loic frasse-mathon
*/

#include "client.h"

void	set_window_pos(t_client *client)
{
  if (client->id == 1)
    putenv("SDL_VIDEO_WINDOW_POS=0,0");
  else
    putenv("SDL_VIDEO_WINDOW_POS=0,400");
}

int	get_nb_elem(t_client *client, char c)
{
  int	i;
  int	j;
  int	nb;

  i = 0;
  nb = 0;
  while (client->map && client->map->data && i < client->map->height)
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

void		puts_dots(t_client *client, SDL_Surface *ecran)
{
  SDL_Rect	position;
  SDL_Surface	*electric_field[get_nb_elem(client, 'e')];
  SDL_Surface	*coins[get_nb_elem(client, 'c')];
  int		i;
  int		j;
  int		x;
  int		y;

  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 102));
  i = 0;
  x = 0;
  y = 0;
  while (client->map && client->map->data && i < client->map->height)
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
	  else if (client->map->data[i][j] == 'c')
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

void		my_display(t_client *client)
{
  SDL_Surface	*ecran;
  int		size[2];

  size[0] = client->map ? client->map->width * SIZE : 96 * SIZE;
  size[1] = client->map ? client->map->height * SIZE : 10 * SIZE;
  ecran = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  set_window_pos(client);
  ecran = SDL_SetVideoMode(size[0], size[1], 32, SDL_RESIZABLE);
  if (ecran == NULL)
    my_exit("Impossible de charger le mode vidéo", 1);
  SDL_WM_SetCaption("JetPack2Tek3", NULL);
  puts_dots(client, ecran);
  SDL_Flip(ecran);
  my_pause(client, ecran);
  SDL_Quit();
}

void		my_pause(t_client *client, SDL_Surface *ecran)
{
  int		continuer;
  SDL_Event	event;

  continuer = 1;
  while (continuer)
    {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT)
	continuer = 0;
      puts_dots(client, ecran);
      usleep(25000);
    }
}
