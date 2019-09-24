#ifndef MULTI_USER_SOCKETS_CHAT_MESSAGE_H
#define MULTI_USER_SOCKETS_CHAT_MESSAGE_H

#define MAX_MESSAGE_SIZE 200
#define MAX_SENDER_SIZE 20

#define TRUE 1
#define FALSE 0

enum MESSAGE_TYPE {
    PRESENTATION_TYPE, NORMAL_TYPE, TERMINATE_TYPE
};

#include <time.h>

struct Message {
    char sender[MAX_SENDER_SIZE];   /* sender of text */
    char text[MAX_MESSAGE_SIZE];    /* text text */
    struct tm tm;                   /* date value */
    enum MESSAGE_TYPE type;         /* message type */
};

#endif //MULTI_USER_SOCKETS_CHAT_MESSAGE_H