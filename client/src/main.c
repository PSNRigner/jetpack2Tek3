#include "client.h"

static void     init_client(t_client *client)
{
  client->ip = NULL;
  client->port = -1;
  client->socket_cli = -1;
  client->id = -1;
  client->map = NULL;
}

static void     parse_args(t_client *client, int ac, char **av)
{
  int           i;

  i = 1;
  while (i < ac)
    {
      if (!strcmp(av[i], "-h") && i + 1 < ac)
	client->ip = av[++i];
      else if (!strcmp(av[i], "-p") && i + 1 < ac)
	client->port = atoi(av[++i]);
      else
	my_exit("Invalid argument.", 1);
      i++;
    }
    if (client->port == -1 || client->ip == NULL)
      my_exit("Missing some information to startup.", 1);
}

void            my_connect(t_client *client)
{
    struct      sockaddr_in server;
    
    client->socket_cli = socket(AF_INET , SOCK_STREAM , 0);
    if (client->socket_cli == -1)
        my_exit("Could not create socket", 1);
    puts("Socket created");
    server.sin_addr.s_addr = inet_addr(client->ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(client->port);
    if (connect(client->socket_cli , (struct sockaddr *)&server , sizeof(server)) < 0)
        my_exit("Could not create socket", 1);
    puts("Connected");
    get_client_id(client);
    read_map(client);
}

void            my_client_core(t_client *client)
{
    printf("%i\n", client->id);
}

int             main(int ac, char **av)
{
    t_client    client;

    init_client(&client);
    parse_args(&client, ac, av);
    my_connect(&client);
    my_display(&client);
    return (0);
}
