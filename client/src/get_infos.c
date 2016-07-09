/*
** get_infos.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:53:39 2016 loic frasse-mathon
** Last update Fri Jul  8 15:54:22 2016 loic frasse-mathon
*/

#include "client.h"

void	get_client_id(t_client *client)
{
  char	server_reply[2000];
  int	nb;
  int	i;

  if (send(client->socket_cli , "ID\n", strlen("ID\n") , 0) < 0)
    my_exit("Send failed", 1);
  if ((nb = recv(client->socket_cli, server_reply , 2000 , 0)) < 0)
    my_exit("recv failed", 1);
  server_reply[nb] = '\0';
  i = 0;
  while (server_reply[i])
    {
      if (isdigit(server_reply[i]))
	       client->id = digit_to_int(server_reply[i]);
      ++i;
    }
}
