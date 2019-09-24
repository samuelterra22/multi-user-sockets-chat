/* Server side implementation of UDP client-server model */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAX_LINE 1024

/* Driver code */
int main() {
    int sock_fd;
    char buffer[MAX_LINE];
    char *welcome_message = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    /* Creating socket file descriptor */
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    /* Filling server information */
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    /* Bind the socket with the server address */
    if (bind(sock_fd, (const struct sockaddr *) &servaddr,
             sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    n = recvfrom(sock_fd, (char *) buffer, MAX_LINE, MSG_WAITALL,
                 (struct sockaddr *) &cliaddr, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sock_fd, (const char *) welcome_message, strlen(welcome_message),
           MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
    printf("Hello message sent.\n");

    return EXIT_SUCCESS;
}