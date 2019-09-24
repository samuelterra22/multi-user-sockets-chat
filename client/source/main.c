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

#include "../../lib/message.h"

#define PORT     8080

int main() {
    int sock_fd;
    struct sockaddr_in serve_addr;

    struct Message newMess = {"mensagem vinda do cliente"};

    /* Creating socket file descriptor */
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serve_addr, 0, sizeof(serve_addr));

    /* Filling server information */
    serve_addr.sin_family = AF_INET;
    serve_addr.sin_port = htons(PORT);
    serve_addr.sin_addr.s_addr = INADDR_ANY;

    sendto(sock_fd, (struct Message *) &newMess, sizeof(newMess), MSG_CONFIRM,
           (const struct sockaddr *) &serve_addr, sizeof(serve_addr));

    close(sock_fd);
    return EXIT_SUCCESS;
}