/*
** client.h for  in /home/frasse_l/Projets/jetpack2Tek3
** 
** Made by loic frasse-mathon
** Login   <frasse_l@epitech.net>
** 
** Started on  Fri Jul  8 15:51:20 2016 loic frasse-mathon
** Last update Tue Jul 12 12:12:46 2016 loic frasse-mathon
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <ctype.h>
# include <pthread.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <pthread.h>

# define SIZE		19
# define COMMANDS	6
# define READ_LEN	4
# define CHECKC		client->map->data[i[0]][i[1]] == 'c'
# define CHECKE		client->map->data[i[0]][i[1]] == 'e'

enum			tile_type
  {
    EMPTY,
    COIN,
    LASER
  };

typedef struct		s_command
{
  char			*str;
  void			(*func)(void *, int, char **);
}			t_command;

typedef struct		s_str
{
  char			*str;
  struct s_str		*next;
}			t_str;

typedef struct  	s_player
{
	int 			id;
	double 			x;
	double 			y;
	int 			score;
	struct s_player *next;
}			t_player;

typedef struct		s_map
{
  int			width;
  int			height;
  char			**data;
}			t_map;

typedef struct 		s_client
{
  char *		ip;
  int 			id;
  fd_set		fds;
  int 			port;
  t_map			*map;
  fd_set		rdfds;
  pthread_t		thread;
  char			started;
  char			received;
  int 			socket_cli;
  t_player		*players;
  t_command		commands[COMMANDS];
} 			t_client;

int		my_atoi(char *);
double		my_atof(char *);
void		*xmalloc(size_t);
int 		digit_to_int(char);
char		*get_next_line(int);
void 		my_exit(char *, int);
void		my_select(t_client *);
void 		my_display(t_client *);
void 		get_client_id(t_client *);
char		**split_str(char *, char);
void  		set_window_pos(t_client *);
int 		get_nb_elem(t_client *, char);
void		display_map(char **, int, int);
int		my_strcmp_case(char *, char *);
void		cmd_id(t_client *, int, char **);
void		cmd_map(t_client *, int, char **);
void		cmd_start(t_client *, int, char **);
void		cmd_player(t_client *, int, char **);
void 		cmd_coin(t_client *, int, char **);
void 		cmd_finish(t_client *, int , char **);
void		read_map(t_client *, int, int, char *);
void 		create_players(t_client *, SDL_Surface *);
void 		my_pause(t_client *client, SDL_Surface *ecran);
void		display_score(t_client *, SDL_Surface *, SDL_Color);

#endif /* !CLIENT_H_ */
