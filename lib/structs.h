#ifndef MULTI_USER_SOCKETS_CHAT_STRUCTS_H
#define MULTI_USER_SOCKETS_CHAT_STRUCTS_H

#include <time.h>

#include "contants.h"

enum MESSAGE_TYPE {
	PRESENTATION_TYPE, NORMAL_TYPE, TERMINATE_TYPE, HISTORY_TYPE, END_HISTORY
};

struct Message {
	char sender[MAX_SENDER_SIZE];   /* sender of text */
	char text[MAX_MESSAGE_SIZE];    /* text text */
	struct tm tm;                   /* date value */
	enum MESSAGE_TYPE type;         /* message type */
};

struct tList {
	struct Message message;
	struct tList *next;
};

typedef struct tList List;

#endif //MULTI_USER_SOCKETS_CHAT_STRUCTS_H
