#ifndef MULTI_USER_SOCKETS_CHAT_MESSAGE_H
#define MULTI_USER_SOCKETS_CHAT_MESSAGE_H

#include <netinet/in.h>

#include "../structs.h"

/******************************************************************************
 * Send mounted message.
 *****************************************************************************/
void send_message(struct Message message, int sock_fd, struct sockaddr_in serve_addr);

/******************************************************************************
 * Mount message using attribute values.
 *****************************************************************************/
void mount_and_send_message(char *sender_name, char *text, enum MESSAGE_TYPE type,
							int sock_fd, struct sockaddr_in serve_addr);

/******************************************************************************
 * Send presentation message for server with flag PRESENTATION_TYPE.
 *****************************************************************************/
void send_presentation_message(char *sender_name, int sock_fd, struct sockaddr_in serve_addr);

/******************************************************************************
 * Send terminate message for server with flag TERMINATE_TYPE.
 *****************************************************************************/
void send_terminate_message(char *sender_name, int sock_fd, struct sockaddr_in serve_addr);

/******************************************************************************
 * Send a normal message for server with flag NORMAL_TYPE.
 *****************************************************************************/
void send_normal_message(char *sender_name, char *text, int sock_fd, struct sockaddr_in serve_addr);

/******************************************************************************
 * Print a message
 *****************************************************************************/
void print_message(struct Message *message);

/******************************************************************************
 * Show message history received from server
 *****************************************************************************/
void show_history(int sock_fd, struct sockaddr_in serve_addr);

/******************************************************************************
 * Send message list for client
 *****************************************************************************/
void send_history(int sock_fd, struct sockaddr_in cli_addr, List *list);

#endif //MULTI_USER_SOCKETS_CHAT_MESSAGE_H