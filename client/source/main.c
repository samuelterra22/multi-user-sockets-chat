/******************************************************************************
 * Client side implementation of UDP client-server model                      *
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
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "../../lib/message/message.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

/* Socket port */
#define PORT 8080

/******************************************************************************
 * Struct de arumento da thread.
 *****************************************************************************/
typedef struct {
	int sock_fd;
	struct sockaddr_in serve_addr;
} arg;

/******************************************************************************
 * Método thread.
 *
 * @param	arguments	Argumentos da thread.
 *
 * @return	void
 *****************************************************************************/
void *listen_server(void *arguments) {
	arg *args = (arg *) arguments;

	struct Message *message = malloc(sizeof(struct Message));

	while (1) {
		unsigned int len = sizeof(args->serve_addr);
		recvfrom(args->sock_fd, (struct Message *) message, sizeof(struct Message), MSG_WAITALL,
				 (struct sockaddr *) &args->serve_addr, &len);
		print_message(message);

		usleep(300 * 1000);
	}
}

/******************************************************************************
 * Método responsável por disparar a thread de ficar ouvindo as respostas do
 * servidor.
 *
 * @param	sock_fd
 * @param	serve_addr
 *
 * @return	void
 *****************************************************************************/
void initialize_threads(int sock_fd, struct sockaddr_in serve_addr) {
	arg *arguments = malloc(sizeof(arg));
	arguments->sock_fd = sock_fd;
	arguments->serve_addr = serve_addr;

	pthread_t thread_id;

	if (pthread_create(&thread_id, NULL, listen_server, (void *) arguments) != 0) {
		printf("Thread not created.\n");
		exit(0);
	}
}

/******************************************************************************
 * Função principal do cliente.
 *
 * @param	argc
 * @param	argv
 *
 * @return	Status de saída do progama.
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

	/* initialize thread to listen messages from server */
	initialize_threads(sock_fd, serve_addr);

	/* main application loop */
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

#pragma clang diagnostic pop