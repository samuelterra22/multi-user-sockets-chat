/******************************************************************************
 * Structs utilizadas no trabalho.					                      	  *
 * Estratégia utilizada para evitar dependências circulares                   *
 *                                                                            *
 * File:    structs.c                                                         *
 * Author:  Samuel Terra Vieira                                               *
 * Address: Universidade Federal de Lavras                                    *
 * Date:    Out/2019                                                          *
 *****************************************************************************/

#ifndef MULTI_USER_SOCKETS_CHAT_STRUCTS_H
#define MULTI_USER_SOCKETS_CHAT_STRUCTS_H

#include <time.h>

#include "constants.h"

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
	struct Message message;            /* message sent */
	struct tList *next;                /* pointer to next node */
};

typedef struct tList List;

#endif //MULTI_USER_SOCKETS_CHAT_STRUCTS_H
