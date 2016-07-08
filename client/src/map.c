#include "client.h"

void     get_map_infos(char *buffer, t_map *map)
{
  int   i;
  char  size[10];
  int   x;
  
  i = 0;
  x = 0;
   while (buffer[i++] != '_')
  {
    if (buffer[i] == 'P')
    {
      i++;
      while (isdigit(buffer[++i]))
        size[x++] = buffer[i];
      map->width = atoi(size);
      size[0] = '\0';
      i++;
      x = 0;
      while (isdigit(buffer[i]))
        size[x++] = buffer[i++];
      map->height = atoi(size);
    }
  }
}

void    get_map_data(char *buffer, t_map *map)
{
  char  **tab;
  int   i;
  int   j;
  int   x;

  i = 0;
  x = 0;
  tab = malloc(sizeof(char) * map->height);
  while(i <= map->height)
    {
      j = 0;
      tab[i] = malloc(sizeof(char) * map->width);
      while (buffer[x] && j < map->width -1)
      {
        tab[i][j] = buffer[x];
        j++;
        x++;
      }
      x++;
      i++;
    }
    tab[i] = NULL;
    map->data = tab;
}

void  display_map(char **map, int width, int height)
{
  int i;
  int j;

  i = 0;
  while (i < height)
    {
      j = 0;
      while (j <= width && i > 0)
  {
    printf("%c", map[i][j]);
    j++;
  }
      printf("\n");
      i++;
    }
  printf("\n");
}

void	read_map(t_client *client)
{
  char	buffer[4096];
  int   nb;

  if (client->map)
    my_exit("Map already loaded.", 1);
  if(send(client->socket_cli , "MAP\n", strlen("MAP\n") , 0) < 0)
        my_exit("Send map failed", 1);
    if((nb = recv(client->socket_cli, buffer , 4096 , 0)) < 0)
        my_exit("Recv map failed", 1);
    buffer[nb] = '\0';
  client->map = malloc(sizeof(t_map));

  get_map_infos(buffer, client->map);
  printf("%i\n%i\n", client->map->width, client->map->height); 
  get_map_data(buffer, client->map);
}
