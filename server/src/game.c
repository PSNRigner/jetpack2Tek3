/*
** game.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 09:16:26 2016 loic frasse-mathon
** Last update Fri Jul  8 23:44:03 2016 loic frasse-mathon
*/

#include "server.h"

void	finish(t_server *server, int id)
{
  int	i[2];

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
  server->count = server->started = 0;
  i[0] = 0;
  while (i[0] < server->map->width)
    {
      i[1] = 0;
      while (i[1] < server->map->height)
	{
	  if (server->map->data[i[1]][i[0]] == OLD_COIN)
	    server->map->data[i[1]][i[0]] = COIN;
	  i[1]++;
	}
      i[0]++;
    }
}

static void	check_coin(t_server *server, t_player *player, int x, int y)
{
  y = server->map->height - y - 1;
  if (x < 0 || x >= server->map->width || y < 0 || y >= server->map->height)
    return ;
  if (server->map->data[y][x] == COIN)
    {
      player->score++;
      server->map->data[y][x] = OLD_COIN;
      y = server->map->height - y - 1;
      dprintf(server->players->fd, "COIN %d %d %d\n", player->id, x, y);
      dprintf(server->players->next->fd, "COIN %d %d %d\n", player->id, x, y);
    }
  else if (server->map->data[y][x] == LASER)
    player->dead = 1;
}

static void	move_vertical(t_server *server, t_player *player)
{
  double	y;
  double	vel;

  player->velocity += server->gravity * -1 * (double)(player->firing * 2 - 1)
    * (double)TIMEOUT / (double)1000000;
  y = player->y;
  y += player->velocity * (double)TIMEOUT / (double)1000000;
  vel = 0;
  if (y < 0)
    y = 0;
  else if (y > server->map->height - 1)
    y = server->map->height - 1;
  else
    vel = player->velocity;
  player->velocity = vel;
  player->y = y;
}

static int	move(t_server *server)
{
  double	diff;

  diff = (double)SPEED * (double)TIMEOUT;
  diff /= (double)1000000;
  server->players->x += diff;
  server->players->next->x += diff;
  move_vertical(server, server->players);
  move_vertical(server, server->players->next);
  check_coin(server, server->players, server->players->x, server->players->y);
  check_coin(server, server->players, server->players->x + 0.99,
	     server->players->y);
  check_coin(server, server->players, server->players->x,
	     server->players->y + 0.99);
  check_coin(server, server->players, server->players->x + 0.99,
	     server->players->y + 0.99);
  check_coin(server, server->players->next, server->players->next->x,
	     server->players->next->y);
  check_coin(server, server->players->next, server->players->next->x + 0.99,
	     server->players->next->y);
  check_coin(server, server->players->next, server->players->next->x,
	     server->players->next->y + 0.99);
  check_coin(server, server->players->next, server->players->next->x + 0.99,
	     server->players->next->y + 0.99);
  return (check_end(server));
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
  if (move(server))
    return ;
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
