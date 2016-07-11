/*
** server.h for  in /home/frasse_l/Projets/jetpack2Tek3/server/include
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Thu Jul  7 09:40:58 2016 loic frasse-mathon
** Last update Mon Jul 11 10:07:41 2016 loic frasse-mathon
*/

/*
** Main header for jetpack2Tek3 server
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/select.h>

# define CMDS		4
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
    LASER,
    OLD_COIN
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
  double		x;
  double		y;
  int			id;
  int			fd;
  char			dead;
  char			ready;
  int			score;
  char			firing;
  double		velocity;
  struct s_player	*next;
}			t_player;

/*
** Server / network struct
*/

typedef struct		s_server
{
  fd_set		fds;
  struct protoent       *pe;
  struct sockaddr_in    sin;
  t_map			*map;
  int			port;
  int			sock;
  int			count;
  fd_set                rdfds;
  int                   max_fd;
  int			gravity;
  char			started;
  struct timeval	timeout;
  t_player		*players;
  t_command		cmds[CMDS];
}			t_server;

int			g_sock;

/*
** Server functions
*/

void		tick(t_server *);
int		check_end(t_server *);
void		finish(t_server *, int);
void		init_network(t_server *);
void		add_player(t_server *, int);
void		read_map(t_server *, char *);
void		remove_player(t_server *, int);
void		perform_cmd(t_server *, t_player *, char *);

/*
** Utils functions
*/

void		ctrl_c(int);
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
void		cmd_fire(t_server *, t_player *, int, char **);
void		cmd_ready(t_server *, t_player *, int, char **);

#endif /* !SERVER_H_ */
