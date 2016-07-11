/*
** select.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Mon Jul 11 09:55:11 2016 loic frasse-mathon
** Last update Mon Jul 11 10:18:17 2016 loic frasse-mathon
*/

#include "client.h"

static void	free_tab(char **tab)
{
  if (!tab)
    return ;
  if (tab[0])
    free(tab[0]);
  free(tab);
}

static void	perform_cmd(t_client *client, char *cmd)
{
  char		**tab;
  int		i;
  int		n;

  tab = split_str(cmd, ' ');
  n = 0;
  while (tab && tab[n])
    n++;
  if (n == 0)
    {
      free_tab(tab);
      return ;
    }
  i = 0;
  while (i < COMMANDS)
    {
      if (!my_strcmp_case(client->commands[i].str, tab[0]))
	{
	  client->commands[i].func(client, n, tab);
	  free_tab(tab);
	  return ;
	}
      i++;
    }
}

static void	read_command(t_client *client, int sock)
{
  char		*buffer;
  int		ret;

  if (!(buffer = get_next_line(sock)) || feof(fdopen(sock, "r")))
    {
      close(sock);
      exit(0);
    }
  ret = strlen(buffer);
  buffer[ret] = 0;
  if (buffer[ret - 1] == '\n')
    buffer[ret - 1] = 0;
  if (ret > 1 && buffer[ret - 2] == '\r')
    buffer[ret - 2] = 0;
  perform_cmd(client, buffer);
}

void	my_select(t_client *client)
{
  int	ret;

  FD_ZERO(&client->fds);
  FD_SET(client->socket_cli, &client->fds);
  while (1)
    {
      client->rdfds = client->fds;
      if ((ret = select(FD_SETSIZE, &client->rdfds, NULL, NULL,
			NULL)) < 0)
        my_exit(NULL, 1);
      if (ret > 0 && FD_ISSET(client->socket_cli, &client->rdfds))
        read_command(client, client->socket_cli);
    }
}
