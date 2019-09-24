#include "list.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../lib/message.h"

struct tList {
    struct Message message;
    struct tList *next;
};

void insert_list(List **p, struct Message message) {
    List *current, *new, *previous;

    new = (List *) malloc(sizeof(List));

    current = *p;
    previous = NULL;

    new->message = message;

    if (current == NULL) {
        new->next = NULL;
        *p = new;
    } else {
        while (current != NULL) {
            previous = current;
            current = current->next;
        }
        previous->next = new;

    }
}

void print_list(List *p) {
    while (p != NULL) {
        printf("[%d:%d:%d, %d/%d/%d] %s %s \n",
               p->message.tm.tm_hour, p->message.tm.tm_min, p->message.tm.tm_sec,
               p->message.tm.tm_mday, p->message.tm.tm_mon + 1, 1900 + p->message.tm.tm_year,
               p->message.sender, p->message.text);
        p = p->next;
    }
}

void *destroy_list(List *l) {
    List *p = l;
    while (p != NULL) {
        List *t = p->next;
        free(p);
        p = t;
    }
    return NULL;
}

List *search_in_list_by_sender(List *list, const char *sender) {
    List *p;
    for (p = list; p != NULL; p = p->next) {
        if (p->message.sender == sender) {
            return p;
        }
    }
    return NULL;
}

List *remove_in_list(List *list, const char *sender) {
    // ponteiro para o elemento anterior
    List *preview = NULL;

    // ponteiro para percorrer a lista
    List *p = list;

    // procura o elemento na lista, guardando o anterior
    while (p != NULL && p->message.sender != sender) {
        preview = p;
        p = p->next;
    }

    // verifica se achou o anterior
    if (p == NULL) {
        // se nao achou, retorna a lista original
        return list;
    }

    // retira o elemento
    if (preview == NULL) {
        // retira elemento do inicio
        list = p->next;
    } else {
        // retira elemento do meio da lista
        preview->next = p->next;
    }

    // libera memório do ponteiro que foi utilizado para percorrer a lista
    free(p);

    return list;
}

/****************************************************
 * Função resposável por verificar se a lista de
 * usuários está vazia.
 *
 * @param list  Ponteiro para lista de usuários.
 *
 * @return Retorna 1 quando a lista for vazia ou 0
 * caso contrário.
 ***************************************************/
int is_empty(List *list) {
    return list == NULL;
}

/****************************************************
 * Função resposável por inicializar uma lista de
 * usuários.
 *
 * @param void
 *
 * @return Retorna NULL, "inicializando" a lista.
 ***************************************************/
List *init_list(void) {
    return NULL;
}