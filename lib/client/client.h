#ifndef MULTI_USER_SOCKETS_CHAT_CLIENT_H
#define MULTI_USER_SOCKETS_CHAT_CLIENT_H

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#include "../structs.h"

int exists_client_address(struct sockaddr_in client_addr);

/* return the first position to add a client */
int get_position_to_add_client();

int get_current_position_of_client(struct sockaddr_in client_addr);

void add_client_address(struct sockaddr_in client_addr);

void remove_client_address(struct sockaddr_in client_addr);

void send_message_broadcast(struct Message message, int sock_fd);

#endif //MULTI_USER_SOCKETS_CHAT_CLIENT_H
