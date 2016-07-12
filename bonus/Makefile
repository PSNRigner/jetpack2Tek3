##
## Makefile for  in /home/frasse_l/Projets/jetpack2Tek3
## 
## Made by loic frasse-mathon
## Login   <frasse_l@epitech.net>
## 
## Started on  Thu Jul  7 09:06:02 2016 loic frasse-mathon
## Last update Tue Jul 12 11:58:37 2016 loic frasse-mathon
##

CLIENT_NAME	= clientJ2T3

CLIENT_SRC	= client/src/main.c \
		client/src/utils.c \
		client/src/my_displayer.c \
		client/src/map.c \
		client/src/select.c \
		client/src/get_next_line.c \
		client/src/commands.c \
		client/src/commands2.c \
		client/src/utils2.c

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

LDFLAGS		= -L./client/lib/ -lSDL -lpthread -ldl -lm -lX11 -lpthread -lSDL_image -lSDL_ttf -lfreetype -lpng -lz

CFLAGS		= -W -Wall -Werror -Wextra -g -I./client/include -I./server/include

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
