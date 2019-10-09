/******************************************************************************
 * Server side implementation of UDP client-server model                      *
 *                                                                            *
 * File:    main.c                                                            *
 * Author:  Samuel Terra Vieira                                               *
 * Address: Universidade Federal de Lavras                                    *
 * Date:    Out/2019                                                          *
 *****************************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

/* Socket port */
#define PORT 8080
#define MAX_CLIENTS 100

#include "../../lib/message/message.h"
#include "../../lib/list/list.h"

struct sockaddr_in client_addresses[MAX_CLIENTS] = {0};
unsigned char clients_control[MAX_CLIENTS] = {0};

int exists_client_address(struct sockaddr_in client_addr) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (memcmp(&client_addresses[i], &client_addr, sizeof(client_addr)) == 0
			&& clients_control[i] == 1) {
			return TRUE;
		}
	}
	return FALSE;
}

// return the first position to add a client
int get_position_to_add_client() {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients_control[i] == 0) {
			return i;
		}
	}
	return -1;
}

void add_client_address(struct sockaddr_in client_addr) {
	if (!exists_client_address(client_addr)) {
		int position = get_position_to_add_client();
		if (position != -1) {
			memcpy(&client_addresses[position], &client_addr, sizeof(struct sockaddr_in));
			clients_control[position] = 1;
		} else {
			printf("Sala cheia\n");
		}
	}
}

void send_message_broadcast(struct Message message, int sock_fd) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients_control[i] == 1) {
			sendto(sock_fd, (struct Message *) &message, sizeof(struct Message), MSG_CONFIRM,
				   (const struct sockaddr *) &client_addresses[i], sizeof(client_addresses[i]));
		}
	}
}

int main(int argc, char *argv[]) {
	int sock_fd;
	struct sockaddr_in serve_addr, cli_addr;

	struct Message *message = malloc(sizeof(struct Message));
	List *messages_history = init_list();

	/* Creating socket file descriptor */
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&serve_addr, 0, sizeof(serve_addr));
	memset(&cli_addr, 0, sizeof(cli_addr));

	/* Filling server information */
	serve_addr.sin_family = AF_INET; /* IPv4 */
	serve_addr.sin_addr.s_addr = INADDR_ANY; /* Address to accept any incoming messages.  */
	serve_addr.sin_port = htons(PORT); /* Server port */

	/* Bind the socket with the server address */
	if (bind(sock_fd, (const struct sockaddr *) &serve_addr, sizeof(serve_addr)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	printf("Servidor pronto para receber mensagens.\n\n");

	while (TRUE) {
		unsigned int len = sizeof(cli_addr);
		recvfrom(sock_fd, message, sizeof(*message), MSG_WAITALL, (struct sockaddr *) &cli_addr, &len);

		if (message->type == PRESENTATION_TYPE) {
			printf("%s se conectou\n", message->sender);

			// sent history for new client
			send_history(sock_fd, cli_addr, messages_history);
		} else if (message->type == TERMINATE_TYPE || message->type == NORMAL_TYPE) {
			printf("%s se desconectou\n", message->sender);
		}

		/* add client in list */
		add_client_address(cli_addr);

		/* send the message for all clients */
		send_message_broadcast(*message, sock_fd);

		/* save message in history */
		insert_list(&messages_history, *message);
	}
}

#pragma clang diagnostic pop