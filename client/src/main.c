/*
** main.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:54:36 2016 loic frasse-mathon
** Last update Mon Jul 11 11:27:49 2016 loic frasse-mathon
*/

#include "client.h"

static void	init_client(t_client *client)
{
  client->ip = NULL;
  client->port = -1;
  client->socket_cli = -1;
  client->id = -1;
  client->map = NULL;
  client->received = 0;
  client->started = 0;
  client->players = NULL;
}

static void	parse_args(t_client *client, int ac, char **av)
{
  int		i;

  i = 1;
  while (i < ac)
    {
      if (!strcmp(av[i], "-h") && i + 1 < ac)
	client->ip = av[++i];
      else if (!strcmp(av[i], "-p") && i + 1 < ac)
	client->port = atoi(av[++i]);
      else
	my_exit("Invalid argument.", 1);
      i++;
    }
  if (client->port == -1 || client->ip == NULL)
    my_exit("Missing some information to startup.", 1);
}

void		my_connect(t_client *client)
{
  struct	sockaddr_in server;

  client->socket_cli = socket(AF_INET , SOCK_STREAM , 0);
  if (client->socket_cli == -1)
    my_exit("Could not create socket", 1);
  if (strcmp(client->ip, "localhost") == 0)
    client->ip = "127.0.0.1";
  server.sin_addr.s_addr = inet_addr(client->ip);
  server.sin_family = AF_INET;
  server.sin_port = htons(client->port);
  if (connect(client->socket_cli, (struct sockaddr *)&server,
	      sizeof(server)) < 0)
    my_exit("Could not connect socket", 1);
  dprintf(client->socket_cli, "ID\nMAP\n");
  if (pthread_create(&client->thread, NULL,
		     (void *(*)(void *))my_display, client))
    my_exit("Thread creation error", 1);
  my_select(client);
}

void		register_command(t_client *client, char *str,
				 void (*func)(t_client *, int, char **))
{
  static int	id = 0;

  client->commands[id].str = str;
  client->commands[id].func = (void (*)(void *, int, char **))func;
  id++;
}

int		main(int ac, char **av)
{
  t_client	*client;

  client = xmalloc(sizeof(t_client));
  init_client(client);
  register_command(client, "id", cmd_id);
  register_command(client, "map", cmd_map);
  register_command(client, "start", cmd_start);
  register_command(client, "player", cmd_player);
  register_command(client, "coin", cmd_coin);
  register_command(client, "finish", cmd_finish);
  parse_args(client, ac, av);
  my_connect(client);

  return (0);
}
