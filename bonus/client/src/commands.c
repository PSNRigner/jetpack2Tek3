/*
** commands.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Mon Jul 11 10:19:24 2016 loic frasse-mathon
** Last update Tue Jul 12 09:43:20 2016 loic frasse-mathon
*/

#include "client.h"

static void	check_ready(t_client *client)
{
  if (client->received & 1 && client->received & 2)
    dprintf(client->socket_cli, "READY\n");
}

void	cmd_id(t_client *client, int ac, char **av)
{
  if (ac != 2)
    return ;
  client->id = my_atoi(av[1]);
  client->received |= 1;
  check_ready(client);
}

void	cmd_map(t_client *client, int ac, char **av)
{
  int	size[2];

  if (ac != 4)
    return ;
  size[0] = my_atoi(av[1]);
  size[1] = my_atoi(av[2]);
  read_map(client, size[0], size[1], av[3]);
  client->received |= 2;
  check_ready(client);
}

void	cmd_start(t_client *client, int ac, char **av)
{
  (void)ac;
  (void)av;
  client->started = 1;
}

void		cmd_player(t_client *client, int ac, char **av)
{
  t_player	*player;
  t_player	*tmp;
  int		id;

  if (ac != 5)
    return ;
  id = my_atoi(av[1]);
  player = client->players;
  tmp = NULL;
  while (player)
    {
      if (player->id == id)
	tmp = player;
      player = player->next;
    }
  if (tmp == NULL)
    {
      tmp = xmalloc(sizeof(t_player));
      tmp->next = client->players;
      client->players = tmp;
    }
  tmp->id = id;
  tmp->x = my_atof(av[2]);
  tmp->y = my_atof(av[3]);
  tmp->score = my_atoi(av[4]);
}
