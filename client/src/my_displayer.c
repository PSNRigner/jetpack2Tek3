/*
** my_displayer.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:58:11 2016 loic frasse-mathon
** Last update Wed Jul 13 11:34:07 2016 loic frasse-mathon
*/

#include "client.h"

void		puts_dots(t_client *client, SDL_Surface *ecran)
{
  SDL_Rect	position;
  SDL_Surface	*tmp;
  int		i[2];

  i[0] = 0;
  while (client->map && client->map->data && i[0] < client->map->height)
    {
      i[1] = 0;
      while (i[1] < client->map->width)
	{
	  position.x = i[1] * SIZE;
	  position.y = i[0] * SIZE;
	  tmp = SDL_CreateRGBSurface(SDL_HWSURFACE, SIZE, SIZE, 32, 0, 0, 0, 0);
	  SDL_FillRect(tmp, NULL, SDL_MapRGB(ecran->format, CHECKC ? 255
					     : 0, CHECKE ? 100 : CHECKC ?
					     255 : 0, CHECKE ? 150 : CHECKC
					     ? 0 : 102));
	  SDL_BlitSurface(tmp, NULL, ecran, &position);
	  SDL_FreeSurface(tmp);
	  tmp = NULL;
    	  i[1]++;
    	}
      i[0]++;
    }
  create_players(client, ecran);
}

void		create_players(t_client *client, SDL_Surface *ecran)
{
  SDL_Rect	position;
  SDL_Surface	*player;
  t_player	*tmp;
  SDL_Color	color;

  tmp = client->players;
  color.r = 255;
  color.g = 255;
  color.b = 255;

  while  (tmp && client->map)
    {
      position.x = tmp->x * SIZE;
      position.y = (client->map->height - tmp->y - 1) * SIZE;
      player = SDL_CreateRGBSurface(SDL_HWSURFACE, SIZE, SIZE, 32, 0, 0, 0, 0);
      if (tmp->id == client->id)
	SDL_FillRect(player, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
      else
	SDL_FillRect(player, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
      SDL_BlitSurface(player, NULL, ecran, &position);
      tmp = tmp->next;
      SDL_FreeSurface(player);
    }
  display_score(client, ecran, color);
}

void		my_display(t_client *client)
{
  SDL_Surface	*ecran;
  int		size[2];

  size[0] = client->map ? client->map->width * SIZE : 95 * SIZE;
  size[1] = client->map ? client->map->height * SIZE : 10 * SIZE;
  ecran = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  if (TTF_Init() == -1)
    my_exit("Erreur d'initialisation de TTF_Init\n", 1);
  set_window_pos(client);
  ecran = SDL_SetVideoMode(size[0], size[1], 32, SDL_RESIZABLE);
  if (ecran == NULL)
    my_exit("Impossible de charger le mode vidéo", 1);
  SDL_WM_SetCaption("JetPack2Tek3", NULL);
  puts_dots(client, ecran);
  SDL_Flip(ecran);
  my_pause(client, ecran);
  SDL_FreeSurface(ecran);
  TTF_Quit();
  SDL_Quit();
  exit(0);
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
      else if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_SPACE)
	    dprintf(client->socket_cli, "FIRE 1\n");
	}
      else if (event.type == SDL_KEYUP)
        dprintf(client->socket_cli, "FIRE 0\n");
      puts_dots(client, ecran);
      SDL_Flip(ecran);
      usleep(25000);
    }
}
