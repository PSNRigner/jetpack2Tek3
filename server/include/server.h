/*
** server.h for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:40:58 2016 loic frasse-mathon
** Last update Thu Jul  7 17:44:48 2016 loic frasse-mathon
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <ctype.h>

# define CMDS		2
# define READ_LEN	4

enum	tile_type
  {
    EMPTY,
    COIN,
    LASER
  };

typedef struct		s_command
{
  char			*str;
  void			(*func)(void *, void *, int, char **);
}			t_command;

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
  int			count;
  t_map			*map;
  t_command		cmds[CMDS];
  struct sockaddr_in    sin;
  struct protoent       *pe;
  int			sock;
  fd_set                rdfds;
  fd_set		fds;
  int                   max_fd;
  int			port;
  int			gravity;
  char			started;
}			t_server;

void		read_map(t_server *, char *);
int		my_atoi(char *);
void		my_exit(char *, int);
void		init_network(t_server *);
void		cmd_id(t_server *, t_player *, int, char **);
void		remove_player(t_server *, int);
char		**split_str(char *, char);
void		*xmalloc(size_t);
void		perform_cmd(t_server *, t_player *, char *);
void		free_tab(char **);
void		cmd_map(t_server *, t_player *, int, char **);
int		my_strcmp_case(char *, char *);
char		*get_next_line(int);

#endif /* !SERVER_H_ */
