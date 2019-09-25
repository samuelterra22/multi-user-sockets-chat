/******************************************************************************
 * Server side implementation of UDP client-server model                      *
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

#define PORT 8080

#include "../../lib/message.h"
#include "../../lib/list/list.h"

int main() {
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
    serve_addr.sin_addr.s_addr = INADDR_ANY;
    serve_addr.sin_port = htons(PORT);

    /* Bind the socket with the server address */
    if (bind(sock_fd, (const struct sockaddr *) &serve_addr, sizeof(serve_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Servidor pronto para receber mensgens.\n\n");

    while (TRUE) {
        unsigned int len = sizeof(cli_addr);
        recvfrom(sock_fd, message, sizeof(*message), MSG_WAITALL, (struct sockaddr *) &cli_addr, &len);

        insert_list(&messages_history, *message);

        if (message->type == NORMAL_TYPE) {
            printf("[%d:%d:%d, %d/%d/%d] %s: %s \n",
                   message->tm.tm_hour, message->tm.tm_min, message->tm.tm_sec,
                   message->tm.tm_mday, message->tm.tm_mon + 1, 1900 + message->tm.tm_year,
                   message->sender, message->text);
        } else {
            printf("[%d:%d:%d, %d/%d/%d] %s %s \n",
                   message->tm.tm_hour, message->tm.tm_min, message->tm.tm_sec,
                   message->tm.tm_mday, message->tm.tm_mon + 1, 1900 + message->tm.tm_year,
                   message->sender, message->text);

            print_list(messages_history);
        }
    }
}