/*
** main.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/src
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:40:16 2016 loic frasse-mathon
** Last update Thu Jul  7 10:38:31 2016 loic frasse-mathon
*/

#include "server.h"

void		my_exit(char *str, int status)
{
  if (str)
    printf("%s\n", str);
  exit(status ? 84 : 0);
}

void		init_server(t_server *server)
{
  server->players = NULL;
  server->port = -1;
  server->gravity = -1;
  server->map = NULL;
}

void		parse_args(t_server *server, int ac, char **av)
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
}

int		main(int ac, char **av)
{
  t_server	server;

  init_server(&server);
  parse_args(&server, ac, av);
  printf("%d %d\n", server.map->width, server.map->height);
  return (0);
}
