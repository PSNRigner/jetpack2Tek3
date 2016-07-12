/*
** main.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/src
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:40:16 2016 loic frasse-mathon
** Last update Fri Jul  8 11:52:28 2016 loic frasse-mathon
*/

#include "server.h"

void	my_exit(char *str, int status)
{
  if (str)
    printf("%s\n", str);
  exit(status ? 84 : 0);
}

static void	register_cmd(t_server *server, char *name,
			     void (*func)(t_server *, t_player *,
					  int, char **))
{
  static int	i = 0;

  server->cmds[i].str = name;
  server->cmds[i].func = (void (*)(void *, void *,
				   int, char **))func;
  i++;
}

static void	init_server(t_server *server)
{
  server->players = NULL;
  server->port = -1;
  server->gravity = -1;
  server->map = NULL;
  server->count = 0;
  server->started = 0;
  register_cmd(server, "id", cmd_id);
  register_cmd(server, "map", cmd_map);
  register_cmd(server, "fire", cmd_fire);
  register_cmd(server, "ready", cmd_ready);
}

static void	parse_args(t_server *server, int ac, char **av)
{
  int		i;

  i = 1;
  while (i < ac)
    {
      if (!strcmp(av[i], "-g") && i + 1 < ac)
	server->gravity = my_atoi(av[++i]);
      else if (!strcmp(av[i], "-p") && i + 1 < ac)
	server->port = my_atoi(av[++i]);
      else if (!strcmp(av[i], "-m") && i + 1 < ac)
	read_map(server, av[++i]);
      else
	my_exit("Invalid argument.", 1);
      i++;
    }
  if (server->port == -1 || server->gravity == -1 || server->map == NULL)
    my_exit("Missing some information to startup.", 1);
  if (server->port < 0 || server->port > 65535)
    my_exit("Invalid port", 1);
}

int		main(int ac, char **av)
{
  t_server	server;

  g_sock = -1;
  signal(SIGINT, ctrl_c);
  init_server(&server);
  parse_args(&server, ac, av);
  init_network(&server);
  return (0);
}
