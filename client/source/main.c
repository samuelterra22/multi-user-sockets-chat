/******************************************************************************
 * Client side implementation of UDP client-server model                      *
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/time.h>

#include "../../lib/message/message.h"

/* Socket port */
#define PORT 8080


/******************************************************************************
 * Main client function
 *****************************************************************************/
int main(int argc, char *argv[]) {
	int sock_fd;
	struct sockaddr_in serve_addr;
	char text[MAX_MESSAGE_SIZE] = "";
	char sender_name[MAX_SENDER_SIZE];
	int close_connection = FALSE;

	/* Creating socket file descriptor */
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	/* fill memory with a constant byte to server_addr */
	memset(&serve_addr, 0, sizeof(serve_addr));

	/* Filling server information */
	serve_addr.sin_family = AF_INET;
	serve_addr.sin_port = htons(PORT);
	serve_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/* get sender name */
	printf("Informe seu nome: ");
	fgets(sender_name, MAX_SENDER_SIZE, stdin);
	sender_name[strlen(sender_name) - 1] = '\0';

	printf("Você entrou na conversa.\n");
	printf("Digite \"exit\" para sair ou CTRL+C para fechar o programa.\n\n");

	/* inform the server to send presentation message */
	send_presentation_message(sender_name, sock_fd, serve_addr);

	/* show message history received from server */
	show_history(sock_fd, serve_addr);

	while (!close_connection) {

		/* read text from terminal */
		printf("> ");
		fgets(text, MAX_MESSAGE_SIZE, stdin);
		text[strlen(text) - 1] = '\0';

		if (!strcmp(text, "exit")) {
			/* inform the server that client will make exit from chat */
			send_terminate_message(sender_name, sock_fd, serve_addr);

			/* brake main while connection */
			close_connection = TRUE;
			printf("Você saiu da conversa.\n");
			printf("God bye!\n");
		} else {
			/* send message read from terminal */
			send_normal_message(sender_name, text, sock_fd, serve_addr);
		}
	}

	/* close communication socket */
	close(sock_fd);

	return EXIT_SUCCESS;
}