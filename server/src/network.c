/*
** network.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 10:48:28 2016 loic frasse-mathon
** Last update Tue Jul 12 09:54:50 2016 loic frasse-mathon
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
  g_sock = server->sock;
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
  char		*buffer;
  int		ret;
  t_player	*tmp;

  if (!(buffer = get_next_line(sock)) || feof(fdopen(sock, "r")))
    {
      remove_player(server, sock);
      close(sock);
      FD_CLR(sock, &server->fds);
      return ;
    }
  ret = strlen(buffer);
  buffer[ret] = 0;
  if (buffer[ret - 1] == '\n')
    buffer[ret - 1] = 0;
  if (ret > 1 && buffer[ret - 2] == '\r')
    buffer[ret - 2] = 0;
  tmp = server->players;
  while (tmp && tmp->fd != sock)
    tmp = tmp->next;
  if (!tmp)
    return ;
  perform_cmd(server, tmp, buffer);
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
      FD_SET (new, &server->fds);
      if (server->count >= 2)
	{
	  close(new);
	  return ;
	}
      add_player(server, new);
    }
  else
    read_command(server, sock);
}

static void	check(t_server *server, int ret)
{
  int		i;

  if (ret == 0)
    {
      tick(server);
      return ;
    }
  i = 0;
  while (i < FD_SETSIZE)
    {
      if (FD_ISSET(i, &server->rdfds))
	change(server, i);
      i++;
    }
}

void	init_network(t_server *server)
{
  int	ret;

  make_socket(server);
  FD_ZERO(&server->fds);
  FD_SET(server->sock, &server->fds);
  while (1)
    {
      server->rdfds = server->fds;
      server->timeout.tv_sec = 0;
      server->timeout.tv_usec = TIMEOUT;
      if ((ret = select(FD_SETSIZE, &server->rdfds, NULL, NULL,
			&server->timeout)) < 0)
	my_exit(NULL, 1);
      check(server, ret);
    }
}
