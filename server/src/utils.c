/*
** utils.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:52:48 2016 loic frasse-mathon
** Last update Thu Jul  7 15:16:11 2016 loic frasse-mathon
*/

#include "server.h"

int	my_atoi(char *str)
{
  int	i;
  int	n;

  i = 0;
  n = 0;
  if (!str)
    my_exit("Invalid number.", 1);
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	my_exit("Invalid number.", 1);
      n = n * 10 + str[i] - '0';
      i++;
    }
  return (n);
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

static void	add(char **tab, char *str, int *i)
{
  char		*new;
  int		j;

  j = 0;
  new = xmalloc(sizeof(char) * (i[0] - i[1] + 1));
  while (i[1] < i[0])
    {
      new[j] = str[i[1]];
      i[1]++;
      j++;
    }
  new[j] = str[i[1]];
  tab[i[2]] = new;
  i[2]++;
}

char	**split_str(char *str, char delim)
{
  char	**tab;
  int	i[3];

  tab = xmalloc(sizeof(char *) * (count(str, delim) + 1));
  i[0] = 0;
  i[1] = 0;
  i[2] = 0;
  while (str[i[0]])
    {
      if (str[i[0]] == delim)
	{
	  add(tab, str, i);
	  i[1] = i[0] + 1;
	}
      i[0]++;
    }
  if (i[0] != i[1])
    add(tab, str, i);
  tab[i[2]] = NULL;
  return (tab);
}
