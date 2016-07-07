/*
** utils.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:52:48 2016 loic frasse-mathon
** Last update Thu Jul  7 09:55:37 2016 loic frasse-mathon
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
