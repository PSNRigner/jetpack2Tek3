/*
** utils.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:52:48 2016 loic frasse-mathon
** Last update Fri Jul  8 23:30:21 2016 loic frasse-mathon
*/

#include "server.h"

int	my_atoi(char *str)
{
  int	i;
  int	n;
  int	sig;

  i = 0;
  n = 0;
  sig = 1;
  if (!str)
    my_exit("Invalid number.", 1);
  while (str[i])
    {
      if (i == 0 && str[i] == '-')
	sig = -1;
      else if (str[i] < '0' || str[i] > '9')
	my_exit("Invalid number.", 1);
      if (i != 0 || str[i] != '-')
	n = n * 10 + str[i] - '0';
      i++;
    }
  return (n * sig);
}

void	*xmalloc(size_t size)
{
  void	*tmp;

  tmp = malloc(size);
  if (!tmp)
    my_exit("Malloc error.", 1);
  return (tmp);
}

static int	count(char *str, char delim)
{
  int		i;
  int		n;

  i = 0;
  n = 0;
  while (str[i])
    {
      if (str[i] == delim)
	n++;
      i++;
    }
  return (n);
}

char	**split_str(char *str, char delim)
{
  char	**tab;
  int	i;
  char	*tmp;
  char	d[2];

  d[0] = delim;
  d[1] = 0;
  tab = xmalloc(sizeof(char *) * (count(str, delim) + 2));
  i = 0;
  while ((tmp = strtok(i == 0 ? str : NULL, d)))
    {
      tab[i] = tmp;
      i++;
    }
  tab[i] = 0;
  return (tab);
}

int	check_end(t_server *server)
{
  int	first;
  int	second;

  first = server->players->x >= server->map->width - 1
    || server->players->dead;
  second = server->players->next->x >= server->map->width - 1
    || server->players->next->dead;
  if (first || second)
    {
      finish(server, first && second ? -1 : (second ? server->players->id
					     : server->players->next->id));
      return (1);
    }
  return (0);
}
