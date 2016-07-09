/*
** ready.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 17:52:53 2016 loic frasse-mathon
** Last update Sat Jul  9 09:59:49 2016 loic frasse-mathon
*/

#include "server.h"

void		add_player(t_server *server, int socket)
{
  static int	id = 0;
  t_player	*player;
  t_player	*tmp;

  server->count++;
  player = xmalloc(sizeof(t_player));
  player->fd = socket;
  player->x = 0;
  player->y = server->map->height / 2;
  player->score = 0;
  player->velocity = 0;
  player->firing = 0;
  player->ready = 0;
  player->next = NULL;
  player->dead = 0;
  player->id = ++id;
  tmp = server->players;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp)
    tmp->next = player;
  else
    server->players = player;
}

void	cmd_fire(t_server *server, t_player *player, int ac, char **av)
{
  int	fire;

  if (!server->started || ac != 2)
    return ;
  fire = my_atoi(av[1]);
  if (fire == 0)
    player->firing = 0;
  else if (fire == 1)
    player->firing = 1;
  (void)server;
}

void	cmd_ready(t_server *server, t_player *player, int ac, char **av)
{
  if (server->started)
    return ;
  player->ready = 1;
  (void)ac;
  (void)av;
  if (server->count >= 2 && server->players->ready
      && server->players->next->ready)
    {
      server->started = 1;
      dprintf(server->players->fd, "START\n");
      dprintf(server->players->next->fd, "START\n");
    }
}
