/*
** game.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 09:16:26 2016 loic frasse-mathon
** Last update Tue Jul 12 10:20:21 2016 loic frasse-mathon
*/

#include "server.h"

void	finish(t_server *server, t_player *player)
{
  dprintf(player->fd, "FINISH %d\n", player->id);
  close(player->fd);
  FD_CLR(player->fd, &server->fds);
  remove_player(server, player->fd);
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
      dprintf(player->fd, "COIN %d %d %d\n", player->id, x, y);
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

static void	move(t_server *server, t_player *player)
{
  double	diff;

  diff = (double)SPEED * (double)TIMEOUT;
  diff /= (double)1000000;
  player->x += diff;
  move_vertical(server, player);
  check_coin(server, player, player->x, player->y);
  check_coin(server, player, player->x + 0.99,
	     player->y);
  check_coin(server, player, player->x,
	     player->y + 0.99);
  check_coin(server, player, player->x + 0.99,
	     player->y + 0.99);
  check_end(server, player);
}

void		tick(t_server *server)
{
  t_player	*tmp;
  t_player	*tmp2;

  tmp = server->players;
  while (tmp)
    {
      move(server, tmp);
      tmp = tmp->next;
    }
  tmp2 = server->players;
  while (tmp2)
    {
      tmp = server->players;
      while (tmp)
	{
	  dprintf(tmp2->fd, "PLAYER %d %f %f %d\n", tmp->id,
		  tmp->x, tmp->y, tmp->score);
	  tmp = tmp->next;
	}
      tmp2 = tmp2->next;
    }
}
