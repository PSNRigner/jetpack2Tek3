/*
** map.c for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 10:05:53 2016 loic frasse-mathon
** Last update Fri Jul  8 09:54:28 2016 loic frasse-mathon
*/

#include "server.h"

static void	free_list(t_str *list)
{
  if (list)
    {
      free_list(list->next);
      free(list->str);
      free(list);
    }
}

static enum tile_type	*tile_str(char *str)
{
  enum tile_type	*tmp;
  int			i;

  tmp = xmalloc(sizeof(enum tile_type) * strlen(str));
  i = 0;
  while (str[i])
    {
      if (str[i] != '_' && str[i] != 'c' && str[i] != 'e' && str[i] != '\n')
	my_exit("Incorrect map.", 1);
      tmp[i] = str[i] == 'e' ? LASER : (str[i] == 'c' ? COIN : EMPTY);
      i++;
    }
  return (tmp);
}

static void	fill_map(t_server *server, t_str *list)
{
  t_str		*tmp;
  size_t	i[3];

  bzero(i, sizeof(size_t) * 3);
  i[1] = (size_t)-1;
  tmp = list;
  while (tmp)
    {
      i[0]++;
      if (i[1] == (size_t)-1)
	i[1] = strlen(tmp->str);
      else if (i[1] != strlen(tmp->str))
	my_exit("Invalid map.", 1);
      tmp = tmp->next;
    }
  server->map->width = i[1];
  server->map->height = i[0];
  server->map->data = xmalloc(sizeof(char) * i[0] * i[1]);
  tmp = list;
  while (tmp)
    {
      server->map->data[i[2]++] = tile_str(tmp->str);
      tmp = tmp->next;
    }
  free_list(list);
}

static void	add_str(t_str **list, char *buffer)
{
  t_str		*new;
  t_str		*tmp;

  new = xmalloc(sizeof(t_str));
  new->str = strdup(buffer);
  new->next = NULL;
  tmp = *list;
  while (tmp && tmp->next)
    tmp = tmp->next;
  if (!tmp)
    *list = new;
  else
    tmp->next = new;
}

void	read_map(t_server *server, char *path)
{
  char	buffer[4096];
  FILE	*fd;
  t_str	*list;

  if (server->map)
    my_exit("Map already loaded.", 1);
  fd = fopen(path, "r");
  if (fd == NULL)
    {
      perror("Error opening file");
      my_exit(NULL, 1);
    }
  server->map = xmalloc(sizeof(t_map));
  list = NULL;
  while (fgets(buffer, 4096, fd) && !feof(fd))
    {
      if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n')
	buffer[strlen(buffer) - 1] = 0;
      add_str(&list, buffer);
    }
  if (!list)
    my_exit("Empty map file.", 1);
  fill_map(server, list);
  fclose(fd);
}
