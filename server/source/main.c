/******************************************************************************
 * Server side implementation of UDP client-server model                      *
 *                                                                            *
 * File:    main.c                                                            *
 * Author:  Samuel Terra Vieira                                               *
 * Address: Universidade Federal de Lavras                                    *
 * Date:    Out/2019                                                          *
 *****************************************************************************/
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

/* Socket port */
#define PORT 8080

#include "../../lib/message/message.h"
#include "../../lib/list/list.h"

int main(int argc, char *argv[]) {
	int sock_fd;
	struct sockaddr_in serve_addr, cli_addr;

	struct Message *message = malloc(sizeof(struct Message));
	List *messages_history = init_list();

	/* Creating socket file descriptor */
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	////////////////////////////////
	memset(&serve_addr, 0, sizeof(serve_addr));   /* Zero out structure */
	serve_addr.sin_family = AF_INET;                 /* Internet address family */
	serve_addr.sin_addr.s_addr = htonl(INADDR_ANY);/* Broadcast IP address */
	serve_addr.sin_port = htons(PORT);         /* Broadcast port */

	////////////////////////////////

	// memset(&serve_addr, 0, sizeof(serve_addr));
	// memset(&cli_addr, 0, sizeof(cli_addr));

	/* Filling server information */
//	serve_addr.sin_family = AF_INET; /* IPv4 */
//	serve_addr.sin_addr.s_addr = INADDR_ANY;
//	serve_addr.sin_port = htons(PORT);

	/* Bind the socket with the server address */
//	if (bind(sock_fd, (const struct sockaddr *) &serve_addr, sizeof(serve_addr)) < 0) {
//		perror("bind failed");
//		exit(EXIT_FAILURE);
//	}

	printf("Servidor pronto para receber mensagens.\n\n");

	// ------------------------------------------------------
	//	struct Message *message = malloc(sizeof(struct Message));
	recvfrom(sock_fd, message, sizeof(*message), 0, NULL, 0);
	print_message(message);
	printf("recebido do servidor\n");

	// -------------------------------------------------------

	/* Broadcast sendString in datagram to clients every 3 seconds*/

	while (TRUE) {
		unsigned int len = sizeof(cli_addr);
		recvfrom(sock_fd, message, sizeof(*message), 0, (struct sockaddr *) &cli_addr, &len);
		printf("recebido\n");

		insert_list(&messages_history, *message);

		sendto(sock_fd, (struct Message *) &message, sizeof(message), 0, (struct sockaddr *) &serve_addr,
			   sizeof(serve_addr));

		if (message->type == PRESENTATION_TYPE) {
			printf("%s se conectou\n", message->sender);

			/* sent history for new client */
			send_history(sock_fd, cli_addr, messages_history);
		} else if (message->type == TERMINATE_TYPE) {
			printf("%s se desconectou\n", message->sender);
		} else {
			sendto(sock_fd, (struct Message *) &message, sizeof(message), 0, (struct sockaddr *) &serve_addr,
				   sizeof(serve_addr));
//			sendto(sock_fd, (struct Message *) &message, sizeof(message), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, sizeof(cli_addr));
		}
	}
}

#pragma clang diagnostic pop