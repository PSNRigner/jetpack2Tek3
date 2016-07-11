/*
** id.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 13:33:40 2016 loic frasse-mathon
** Last update Mon Jul 11 10:18:10 2016 loic frasse-mathon
*/

#include "server.h"

void		remove_player(t_server *server, int sock)
{
  t_player	*tmp1;
  t_player	*tmp2;

  tmp1 = server->players;
  tmp2 = NULL;
  while (tmp1 && tmp1->fd != sock)
    {
      tmp2 = tmp1;
      tmp1 = tmp1->next;
    }
  if (!tmp1)
    return ;
  server->count--;
  if (tmp2)
    tmp2->next = tmp1->next;
  else
    server->players = tmp1->next;
  free(tmp1);
}

void	perform_cmd(t_server *server, t_player *player, char *cmd)
{
  char	**tab;
  int	i;
  int	n;

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
  while (i < CMDS)
    {
      if (!my_strcmp_case(server->cmds[i].str, tab[0]))
	{
	  server->cmds[i].func(server, player, n, tab);
	  free_tab(tab);
	  return ;
	}
      i++;
    }
}

void	cmd_id(t_server *server, t_player *player, int ac, char **av)
{
  dprintf(player->fd, "ID %d\n", player->id);
  (void)server;
  (void)ac;
  (void)av;
}

void	cmd_map(t_server *server, t_player *player, int ac, char **av)
{
  char	*tmp;
  int	size;
  int	i[3];

  size = server->map->width * server->map->height;
  tmp = xmalloc((size + 1) * sizeof(char));
  i[0] = 0 * ac;
  i[1] = 0;
  while (i[1] < server->map->height)
    {
      i[2] = 0;
      while (i[2] < server->map->width)
	{
	  tmp[i[0]] = server->map->data[i[1]][i[2]] == EMPTY ? '_' :
	    (server->map->data[i[1]][i[2]] == LASER ? 'e' : 'c');
	  i[0]++;
	  i[2]++;
	}
      i[1]++;
    }
  tmp[i[0]] = 0;
  dprintf(player->fd, "MAP %d %d %s\n", server->map->width,
	  server->map->height, tmp);
  free(tmp);
  (void)av;
}

void	free_tab(char **tab)
{
  if (!tab)
    return ;
  if (tab[0])
    free(tab[0]);
  free(tab);
}
