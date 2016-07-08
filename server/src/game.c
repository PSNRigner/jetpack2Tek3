/*
** game.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 09:16:26 2016 loic frasse-mathon
** Last update Fri Jul  8 10:19:49 2016 loic frasse-mathon
*/

#include "server.h"

static void	move(t_server *server)
{
  double	diff;

  diff = (double)SPEED * (double)TIMEOUT;
  diff /= (double)1000000;
  server->players->x += diff;
  server->players->next->x += diff;
}

static void	finish(t_server *server, int id)
{
  if (server->players)
    dprintf(server->players->fd, "FINISH %d\n", id);
  if (server->players && server->players->next)
    dprintf(server->players->next->fd, "FINISH %d\n", id);
  while (server->players)
    {
      close(server->players->fd);
      FD_CLR(server->players->fd, &server->fds);
      remove_player(server, server->players->fd);
    }
  server->started = 0;
}

void	tick(t_server *server)
{
  if (!server->started)
    return ;
  if (server->count != 2)
    {
      finish(server, server->players ? server->players->id : -1);
      return ;
    }
  move(server);
  dprintf(server->players->fd, "PLAYER %d %f %f %d\n", server->players->id,
	  server->players->x, server->players->y, server->players->score);
  dprintf(server->players->fd, "PLAYER %d %f %f %d\n",
	  server->players->next->id, server->players->next->x,
	  server->players->next->y, server->players->next->score);
  dprintf(server->players->next->fd, "PLAYER %d %f %f %d\n",
	  server->players->id, server->players->x, server->players->y,
	  server->players->score);
  dprintf(server->players->next->fd, "PLAYER %d %f %f %d\n",
	  server->players->next->id, server->players->next->x,
	  server->players->next->y, server->players->next->score);
}
