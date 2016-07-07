##
## Makefile for  in /home/frasse_l/Projets/jetpack2Tek3
## 
## Made by loic frasse-mathon
## Login   <frasse_l@epitech.net>
## 
## Started on  Thu Jul  7 09:06:02 2016 loic frasse-mathon
## Last update Thu Jul  7 10:44:49 2016 loic frasse-mathon
##

CLIENT_NAME	= clientJ2T3

CLIENT_SRC	= client/src/main.c

CLIENT_OBJ	= $(CLIENT_SRC:.c=.o)

SERVER_NAME	= serverJ2T3

SERVER_SRC	= server/src/main.c \
		server/src/map.c \
		server/src/utils.c

SERVER_OBJ	= $(SERVER_SRC:.c=.o)

CC		= gcc

LDFLAGS		= 

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
