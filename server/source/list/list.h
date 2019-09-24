#ifndef MULTI_USER_SOCKETS_CHAT_LIST_H
#define MULTI_USER_SOCKETS_CHAT_LIST_H

#include "../../../lib/message.h"

typedef struct tList List;

void insert_list(List **p, struct Message message);

void print_list(List *p);

void *destroy_list(List *l);

List *search_in_list_by_sender(List *list, const char *sender);

List *remove_in_list(List *list, const char *sender);

int is_empty(List *list);

List *init_list(void);

#endif //MULTI_USER_SOCKETS_CHAT_LIST_H
