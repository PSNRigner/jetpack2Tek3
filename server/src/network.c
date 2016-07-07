/*
** network.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 10:48:28 2016 loic frasse-mathon
** Last update Thu Jul  7 15:16:49 2016 loic frasse-mathon
*/

#include "server.h"

static void	make_socket(t_server *server)
{
  server->sock = socket(PF_INET, SOCK_STREAM, 0);
  if (server->sock < 0)
    {
      perror ("socket");
      my_exit(NULL, 1);
    }

  server->sin.sin_family = AF_INET;
  server->sin.sin_port = htons(server->port);
  server->sin.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind (server->sock, (struct sockaddr *)&server->sin,
	    sizeof (server->sin)) < 0)
    {
      perror ("bind");
      my_exit(NULL, 1);
    }

  if (listen(server->sock, 1) < 0)
    {
      perror ("listen");
      my_exit(NULL, 1);
    }
}

static void	read_command(t_server *server, int sock)
{
  char		buffer[4096];
  int		ret;
  t_player	*tmp;

  if ((ret = read(sock, buffer, 4096)) <= 0)
    {
      printf("Client disconnected\n");
      remove_player(server, sock);
      close(sock);
      FD_CLR(sock, &server->fds);
      return ;
    }
  buffer[ret] = 0;
  if (buffer[ret - 1] == '\n')
    buffer[ret - 1] = 0;
  if (ret > 1 && buffer[ret - 2] == '\r')
    buffer[ret - 2] = 0;
  tmp = server->players;
  while (tmp && tmp->fd != sock)
    tmp = tmp->next;
  printf("Received order (id=%d) : %s\n", tmp ? tmp->id : -1, buffer);
  if (!tmp)
    return ;
  perform_cmd(server, tmp, buffer);
}

static void		add_player(t_server *server, int socket)
{
  static int		id = 0;
  t_player		*player;
  t_player		*tmp;

  player = xmalloc(sizeof(t_player));
  player->fd = socket;
  player->x = 0;
  player->y = 0;
  player->score = 0;
  player->firing = 0;
  player->ready = 0;
  player->next = NULL;
  player->id = id++;
  tmp = server->players;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (tmp)
    tmp->next = player;
  else
    server->players = player;
  server->count++;
}

static void		change(t_server *server, int sock)
{
  int			new;
  struct sockaddr_in	client;
  socklen_t		size;

  if (sock == server->sock)
    {
      size = sizeof(client);
      new = accept(sock, (struct sockaddr *)&client, &size);
      if (new < 0)
	return ;
      printf("New connection from %s:%hu\n",
	     inet_ntoa(client.sin_addr),
	     ntohs(client.sin_port));
      FD_SET (new, &server->fds);
      if (server->count >= 2)
	{
	  printf("Server full\n");
	  close(new);
	  return ;
	}
      add_player(server, new);
    }
  else
    read_command(server, sock);
}

void	init_network(t_server *server)
{
  int	i;

  make_socket(server);
  FD_ZERO(&server->fds);
  FD_SET(server->sock, &server->fds);
  printf("Listening on port %d\n", server->port);
  while (1)
    {
      server->rdfds = server->fds;
      if (select(FD_SETSIZE, &server->rdfds, NULL, NULL, NULL) < 0)
	{
	  perror("select");
	  my_exit(NULL, 1);
	}
      i = 0;
      while (i < FD_SETSIZE)
	{
	  if (FD_ISSET(i, &server->rdfds))
	    change(server, i);
	  i++;
	}
    }
}
