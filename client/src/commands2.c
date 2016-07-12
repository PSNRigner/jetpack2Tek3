/*
** commands2.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Tue Jul 12 09:41:36 2016 loic frasse-mathon
** Last update Tue Jul 12 12:16:19 2016 loic frasse-mathon
*/

#include "client.h"

void	cmd_coin(t_client *client, int ac, char **av)
{
  int	x;
  int	y;

  if (ac != 4)
    return ;
  x = my_atoi(av[2]);
  y = my_atoi(av[3]);
  if (y < client->map->height && y >= 0 && x < client->map->width && x >= 0)
    client->map->data[client->map->height - y - 1][x] = '_';
}

void	cmd_finish(t_client *client, int ac, char **av)
{
  int	id;

  if (ac != 2)
    return ;
  id = atoi(av[1]);
  if (id == -1)
    printf("Nobody wins\n");
  else if (client->id == id)
    printf("You win!\n");
  else
    printf("You loose!\n");
  close(client->socket_cli);
  exit(EXIT_SUCCESS);
}

void		display_score(t_client *client, SDL_Surface *ecran,
			      SDL_Color color)
{
  TTF_Font	*police;
  SDL_Surface	*texte;
  SDL_Rect	position;
  t_player	*tmp;
  char		str[128];

  position.x = 1;
  position.y = 0;
  police = NULL;
  texte = NULL;
  tmp = client->players;
  if (tmp == NULL)
    return ;
  if ((police = TTF_OpenFont("client/font/arial.ttf", 15)) == NULL)
    return ;
  while (tmp)
    {
      if (client->id == tmp->id)
        sprintf(str, "Distance : %.1fm Score : %i", tmp->x, tmp->score);
      tmp = tmp->next;
    }
  texte = TTF_RenderText_Solid(police, str, color);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}
