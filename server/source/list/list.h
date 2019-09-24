#ifndef MULTI_USER_SOCKETS_CHAT_LIST_H
#define MULTI_USER_SOCKETS_CHAT_LIST_H

typedef struct tList List;

void insert_list(List **p, int uid, char *name);

void print_list(List *p);

void *destroy_list(List *l);

List *search_in_list(List *list, int uid);

List *remove_in_list(List *list, int uid);

int is_empty(List *list);

List *init_list(void);

#endif //MULTI_USER_SOCKETS_CHAT_LIST_H
