//
// Created by samuel on 24/09/2019.
//

#ifndef MULTI_USER_SOCKETS_CHAT_MESSAGE_H
#define MULTI_USER_SOCKETS_CHAT_MESSAGE_H

#define MAX_MESSAGE_SIZE 200
#define MAX_SENDER_SIZE 20
#define TRUE 1
#define FALSE 0

struct Message {
    char sender[MAX_SENDER_SIZE]; /* sender of message */
    char message[MAX_MESSAGE_SIZE]; /* text message */
};

#endif //MULTI_USER_SOCKETS_CHAT_MESSAGE_H
