//
// Created by samuel on 24/09/2019.
//

#ifndef MULTI_USER_SOCKETS_CHAT_MESSAGE_H
#define MULTI_USER_SOCKETS_CHAT_MESSAGE_H

#define MAX_MESSAGE_SIZE 200

struct Message {
    char message[MAX_MESSAGE_SIZE]; /* text message */
};

#endif //MULTI_USER_SOCKETS_CHAT_MESSAGE_H
