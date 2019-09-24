#include "list.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tList {
    int uid;
    char *name;
    struct tList *next;
};

void insert_list(List **p, int uid, char *name) {
    List *current, *new, *previous;

    new = (List *) malloc(sizeof(List));

    current = *p;
    previous = NULL;

    new->uid = uid;
    new->name = malloc(strlen(name) + 1);
    strcpy(new->name, name);

    if (current == NULL) {
        new->next = NULL;
        *p = new;
    } else {
        while (current != NULL && current->uid < uid) {
            previous = current;
            current = current->next;
        }

        new->next = current;

        if (previous == NULL) {
            *p = new;
        } else {
            previous->next = new;
        }
    }
}

void print_list(List *p) {
    while (p != NULL) {
        printf("%s %d\n", p->name, p->uid);
        p = p->next;
    }
}

void *destroy_list(List *l) {
    List *p = l;
    while (p != NULL) {
        List *t = p->next;
        free(p->name);
        free(p);
        p = t;
    }
    return NULL;
}

List *search_in_list(List *list, int uid) {
    List *p;
    for (p = list; p != NULL; p = p->next) {
        if (p->uid == uid) {
            return p;
        }
    }
    return NULL;
}

List *remove_in_list(List *list, int uid) {
    // ponteiro para o elemento anterior
    List *preview = NULL;

    // ponteiro para percorrer a lista
    List *p = list;

    // procura o elemento na lista, guardando o anterior
    while (p != NULL && p->uid != uid) {
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