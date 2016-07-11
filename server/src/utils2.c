/*
** utils2.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 17:14:04 2016 loic frasse-mathon
** Last update Mon Jul 11 10:16:02 2016 loic frasse-mathon
*/

#include "server.h"

int	my_strcmp_case(char *str1, char *str2)
{
  int	i;

  i = 0;
  while (str1 && str2 && str1[i] && str2[i] &&
	 tolower(str1[i]) == tolower(str2[i]))
    i++;
  return (tolower(str1[i]) - tolower(str2[i]));
}

void	ctrl_c(int sig)
{
  (void)sig;
  if (g_sock != -1)
    close(g_sock);
}
