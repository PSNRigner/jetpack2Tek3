##
## Makefile for  in /home/frasse_l/Projets/jetpack2Tek3
## 
## Made by loic frasse-mathon
## Login   <frasse_l@epitech.net>
## 
## Started on  Thu Jul  7 09:06:02 2016 loic frasse-mathon
## Last update Fri Jul  8 14:42:50 2016 loic frasse-mathon
##

CLIENT_NAME	= clientJ2T3

CLIENT_SRC	= client/src/main.c \
			  client/src/utils.c \
			  client/src/my_displayer.c \
			  client/src/get_infos.c \
			  client/src/map.c

CLIENT_OBJ	= $(CLIENT_SRC:.c=.o)

SERVER_NAME	= serverJ2T3

SERVER_SRC	= server/src/main.c \
		server/src/id.c \
		server/src/map.c \
		server/src/game.c \
		server/src/utils.c \
		server/src/ready.c \
		server/src/utils2.c \
		server/src/network.c \
		server/src/get_next_line.c

SERVER_OBJ	= $(SERVER_SRC:.c=.o)

CC		= gcc

LDFLAGS		= -L./client/lib/ -lSDL -lpthread -ldl -lm -lX11

CFLAGS		= -W -Wall -Werror -Wextra -g -I./client/include -I./server/include -pedantic

all:		client server

client:		$(CLIENT_NAME)

server:		$(SERVER_NAME)

$(CLIENT_NAME):	$(CLIENT_OBJ)
		$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(LDFLAGS)

$(SERVER_NAME):	$(SERVER_OBJ)
		$(CC) -o $(SERVER_NAME) $(SERVER_OBJ)

clean:
		$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean:		clean
		$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re:		fclean all
