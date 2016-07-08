/*
** server.h for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:40:58 2016 loic frasse-mathon
** Last update Fri Jul  8 09:51:53 2016 loic frasse-mathon
*/

/*
** Main header for jetpack2Tek3 server
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

# define CMDS		3
# define READ_LEN	4
# define BUFF_LEN	4096
# define TIMEOUT	25000
# define SPEED		5
/*
** Enum for map tiles
*/

enum	tile_type
  {
    EMPTY,
    COIN,
    LASER
  };

/*
** Command struct
*/

typedef struct		s_command
{
  char			*str;
  void			(*func)(void *, void *, int, char **);
}			t_command;

/*
** String linked list struct, usefull for parsing & buffering
*/

typedef struct		s_str
{
  char			*str;
  struct s_str		*next;
}			t_str;

/*
** Game map struct
*/

typedef struct		s_map
{
  int			width;
  int			height;
  enum tile_type	**data;
}			t_map;

/*
** Player / client struct
*/

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

/*
** Server / network struct
*/

typedef struct		s_server
{
  t_player		*players;
  int			count;
  t_map			*map;
  t_command		cmds[CMDS];
  struct sockaddr_in    sin;
  struct protoent       *pe;
  struct timeval	timeout;
  int			sock;
  fd_set                rdfds;
  fd_set		fds;
  int                   max_fd;
  int			port;
  int			gravity;
  char			started;
}			t_server;

/*
** Server functions
*/

void		tick(t_server *);
void		init_network(t_server *);
void		add_player(t_server *, int);
void		read_map(t_server *, char *);
void		remove_player(t_server *, int);
void		perform_cmd(t_server *, t_player *, char *);

/*
** Utils functions
*/

int		my_atoi(char *);
void		*xmalloc(size_t);
void		free_tab(char **);
char		*get_next_line(int);
void		my_exit(char *, int);
char		**split_str(char *, char);
int		my_strcmp_case(char *, char *);

/*
** Commands functions
*/

void		cmd_id(t_server *, t_player *, int, char **);
void		cmd_map(t_server *, t_player *, int, char **);
void		cmd_ready(t_server *, t_player *, int, char **);

#endif /* !SERVER_H_ */
