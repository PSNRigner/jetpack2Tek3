#include "client.h"

void 	cmd_coin(t_client *client, int ac, char **av)
{
	int 	x;
	int 	y;

	if (ac != 4)
		return ;
	x = my_atoi(av[2]);
	y = my_atoi(av[3]);

	if (y < client->map->height && y >= 0 && x < client->map->width && x >= 0)
	{
		client->map->data[client->map->height - y - 1][x] = '_';
	}
}

void 	cmd_finish(t_client *client, int ac, char **av)
{
	int 		id;

	if (ac != 2)
		return ;
	id = atoi(av[1]);
	if (id == -1)
		printf("Nobody wins\n");
	else if (client->id == id)
		printf("You win!\n");
	else
		printf("You loose!\n");
	close(client->socket_cli);
	exit(EXIT_SUCCESS);
}