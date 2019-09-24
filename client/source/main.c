/******************************************************************************
 * Client side implementation of UDP client-server model                      *
 *                                                                            *
 * File:    main.c                                                            *
 * Author:  Samuel Terra Vieira                                               *
 * Address: Universidade Federal de Lavras                                    *
 * Date:    Nov/2019                                                          *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#include "../../lib/message.h"

#define PORT 8080

void send_message(struct Message message, int sock_fd, struct sockaddr_in serve_addr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    message.tm = tm;

    sendto(sock_fd, (struct Message *) &message, sizeof(message), MSG_CONFIRM,
           (const struct sockaddr *) &serve_addr, sizeof(serve_addr));
}

void mount_and_send_message(char *sender_name, char *text, enum MESSAGE_TYPE type,
                            int sock_fd, struct sockaddr_in serve_addr) {
    struct Message presentation_message;
    presentation_message.type = type;
    strcpy(presentation_message.sender, sender_name);
    strcpy(presentation_message.text, text);
    send_message(presentation_message, sock_fd, serve_addr);
}

void send_presentation_message(char *sender_name, int sock_fd, struct sockaddr_in serve_addr) {
    mount_and_send_message(sender_name, "acabou de entrar na conversa", PRESENTATION_TYPE, sock_fd, serve_addr);
}

void send_terminate_message(char *sender_name, int sock_fd, struct sockaddr_in serve_addr) {
    mount_and_send_message(sender_name, "saiu da conversa", TERMINATE_TYPE, sock_fd, serve_addr);
}

void send_normal_message(char *sender_name, char *text, int sock_fd, struct sockaddr_in serve_addr) {
    mount_and_send_message(sender_name, text, NORMAL_TYPE, sock_fd, serve_addr);
}

int main() {
    int sock_fd;
    struct sockaddr_in serve_addr;
    char text[MAX_MESSAGE_SIZE] = "";
    char sender_name[MAX_SENDER_SIZE];
    int close_connection = FALSE;

    /* Creating socket file descriptor */
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(0);
    }

    memset(&serve_addr, 0, sizeof(serve_addr));

    /* Filling server information */
    serve_addr.sin_family = AF_INET;
    serve_addr.sin_port = htons(PORT);
    serve_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Informe seu nome: ");
    fgets(sender_name, MAX_SENDER_SIZE, stdin);
    sender_name[strlen(sender_name) - 1] = '\0';

    printf("Você entrou na conversa.\n");
    printf("Digite \"exit\" para sair ou CTRL+C para fechar o programa.\n");

    send_presentation_message(sender_name, sock_fd, serve_addr);

    while (!close_connection) {

        printf("> ");
        fgets(text, MAX_MESSAGE_SIZE, stdin);
        text[strlen(text) - 1] = '\0';

        if (!strcmp(text, "exit")) {
            send_terminate_message(sender_name, sock_fd, serve_addr);

            close_connection = TRUE;
            printf("Você saiu da conversa.\n");
            printf("God bye!\n");
        } else {
            send_normal_message(sender_name, text, sock_fd, serve_addr);
        }
    }

    close(sock_fd);
    return EXIT_SUCCESS;
}