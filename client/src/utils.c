/*
** utils.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:57:22 2016 loic frasse-mathon
** Last update Fri Jul  8 16:01:19 2016 loic frasse-mathon
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
