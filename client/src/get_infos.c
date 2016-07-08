#include "client.h"

void get_client_id(t_client *client)
{
	char server_reply[2000];
	int nb, i;

	if(send(client->socket_cli , "ID\n", strlen("ID\n") , 0) < 0)
        my_exit("Send failed", 1);
    if((nb = recv(client->socket_cli, server_reply , 2000 , 0)) < 0)
        my_exit("recv failed", 1);
    server_reply[nb] = '\0';
    for (i = 0; server_reply[i]; ++i)
    {
        if (isdigit(server_reply[i]))
        	client->id = digit_to_int(server_reply[i]);
    }
}