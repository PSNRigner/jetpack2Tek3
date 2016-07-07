/*
** server.h for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:40:58 2016 loic frasse-mathon
** Last update Thu Jul  7 10:17:56 2016 loic frasse-mathon
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <netinet/in.h>

enum	tile_type
  {
    EMPTY,
    COIN,
    LASER
  };

typedef struct		s_str
{
  char			*str;
  struct s_str		*next;
}			t_str;

typedef struct		s_map
{
  int			width;
  int			height;
  enum tile_type	**data;
}			t_map;

typedef struct		s_player
{
  int			fd;
  double		x;
  double		y;
  int			score;
  char			firing;
  char			ready;
  struct s_player	*next;
  int			id;
}			t_player;

typedef struct		s_server
{
  t_player		*players;
  t_map			*map;
  struct sockaddr_in    csin;
  struct sockaddr_in    sin;
  struct protoent       *pe;
  int			fd;
  fd_set                rdfds;
  int                   max_fd;
  int			port;
  int			gravity;
}			t_server;

void		read_map(t_server *, char *);
int		my_atoi(char *);
void		my_exit(char *, int);

#endif /* !SERVER_H_ */
