#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "message.h"

/******************************************************************************
 * Send mounted message.
 *****************************************************************************/
void send_message(struct Message message, int sock_fd, struct sockaddr_in serve_addr) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	message.tm = tm;

	sendto(sock_fd, (struct Message *) &message, sizeof(message), MSG_CONFIRM,
		   (const struct sockaddr *) &serve_addr, sizeof(serve_addr));
}

/******************************************************************************
 * Mount message using attribute values.
 *****************************************************************************/
void mount_and_send_message(char *sender_name, char *text, enum MESSAGE_TYPE type,
							int sock_fd, struct sockaddr_in serve_addr) {
	struct Message presentation_message;
	presentation_message.type = type;
	strcpy(presentation_message.sender, sender_name);
	strcpy(presentation_message.text, text);
	send_message(presentation_message, sock_fd, serve_addr);
}

/******************************************************************************
 * Send presentation message for server with flag PRESENTATION_TYPE.
 *****************************************************************************/
void send_presentation_message(char *sender_name, int sock_fd, struct sockaddr_in serve_addr) {
	mount_and_send_message(sender_name, "acabou de entrar na conversa", PRESENTATION_TYPE, sock_fd, serve_addr);
}

/******************************************************************************
 * Send terminate message for server with flag TERMINATE_TYPE.
 *****************************************************************************/
void send_terminate_message(char *sender_name, int sock_fd, struct sockaddr_in serve_addr) {
	mount_and_send_message(sender_name, "saiu da conversa", TERMINATE_TYPE, sock_fd, serve_addr);
}

/******************************************************************************
 * Send a normal message for server with flag NORMAL_TYPE.
 *****************************************************************************/
void send_normal_message(char *sender_name, char *text, int sock_fd, struct sockaddr_in serve_addr) {
	mount_and_send_message(sender_name, text, NORMAL_TYPE, sock_fd, serve_addr);
}

/******************************************************************************
 * Print a message
 *****************************************************************************/
void print_message(struct Message *message) {
	char *normal_message_format = "[%2d:%2d:%2d, %2d/%2d/%4d] %s: %s \n";
	char *custom_message_format = "[%2d:%2d:%2d, %2d/%2d/%4d] %s %s \n";
	printf(message->type == NORMAL_TYPE ? normal_message_format : custom_message_format,
		   message->tm.tm_hour, message->tm.tm_min, message->tm.tm_sec,
		   message->tm.tm_mday, message->tm.tm_mon + 1, 1900 + message->tm.tm_year,
		   message->sender, message->text);
}

/******************************************************************************
 * Show message history received from server
 *****************************************************************************/
void show_history(int sock_fd, struct sockaddr_in serve_addr) {
	struct Message *message = malloc(sizeof(struct Message));

	while (message->type != END_HISTORY) {
		unsigned int len = sizeof(serve_addr);
		recvfrom(sock_fd, message, sizeof(*message), MSG_WAITALL, (struct sockaddr *) &serve_addr, &len);
		if (message->type != END_HISTORY) {
			print_message(message);
		}
	}
}

/******************************************************************************
 * Send message list for client
 *****************************************************************************/
void send_history(int sock_fd, struct sockaddr_in cli_addr, List *p) {
	while (p != NULL) {
		struct Message message = p->message;
		message.type = HISTORY_TYPE;

		sendto(sock_fd, (struct Message *) &message, sizeof(message),
			   MSG_CONFIRM, (const struct sockaddr *) &cli_addr, sizeof(cli_addr));
		p = p->next;
	}

	struct Message message;
	message.type = END_HISTORY;

	sendto(sock_fd, (struct Message *) &message, sizeof(message),
		   MSG_CONFIRM, (const struct sockaddr *) &cli_addr, sizeof(cli_addr));

}