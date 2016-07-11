/*
** utils.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:57:22 2016 loic frasse-mathon
** Last update Mon Jul 11 10:14:59 2016 loic frasse-mathon
*/

#include "client.h"

void	my_exit(char *str, int status)
{
  if (str)
    printf("%s\n", str);
  exit(status ? 84 : 0);
}

int	digit_to_int(char d)
{
  char	str[2];

  str[0] = d;
  str[1] = '\0';
  return ((int)strtol(str, NULL, 10));
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

void	*xmalloc(size_t	size)
{
  void	*tmp;

  tmp = malloc(size);
  if (!tmp)
    my_exit("Malloc error.", 1);
  return (tmp);
}
