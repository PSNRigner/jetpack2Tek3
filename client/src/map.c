/*
** map.c for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:56:05 2016 loic frasse-mathon
** Last update Mon Jul 11 11:16:45 2016 loic frasse-mathon
*/

#include "client.h"

void	get_map_data(char *buffer, t_map *map)
{
  char	**tab;
  int	i;
  int	j;
  int	x;

  i = 0;
  x = 0;
  tab = xmalloc(sizeof(char *) * map->height);
  while (i < map->height)
    {
      j = 0;
      tab[i] = xmalloc(sizeof(char) * map->width);
      while (buffer[x] && j < map->width)
    	{
    	  tab[i][j] = buffer[x];
    	  j++;
    	  x++;
    	}
      i++;
    }
  map->data = tab;
}

void	read_map(t_client *client, int width, int height, char *buffer)
{
  if (client->map)
    my_exit("Map already loaded.", 1);
  client->map = xmalloc(sizeof(t_map));

  client->map->width = width;
  client->map->height = height;
  get_map_data(buffer, client->map);
}
