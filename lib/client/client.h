#ifndef MULTI_USER_SOCKETS_CHAT_CLIENT_H
#define MULTI_USER_SOCKETS_CHAT_CLIENT_H

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#include "../structs.h"

/******************************************************************************
 * Função reponsável por verificar se já existe endereço de um cliente na lista
 * de clientes.
 *
 * @param	client_addr
 *
 * @return	Retorna booleando informando a existância do endereço do cliente.
 *****************************************************************************/
int exists_client_address(struct sockaddr_in client_addr);

/******************************************************************************
 * Função responsável por retornar a primeira posição vazia para adicionar o
 * cliente.
 *
 * @param	void
 *
 * @return	A posição disponivel.
 *****************************************************************************/
int get_position_to_add_client(void);

/******************************************************************************
 * Função responsável por obter a posição atual de um endereço de um cliente na
 * lista de controle de clientes.
 *
 * @param	client_addr
 *
 * @return	Retorna a posição atual de um endereço na lista de controle.
 *****************************************************************************/
int get_current_position_of_client(struct sockaddr_in client_addr);

/******************************************************************************
 * Método responsável por adicionar um novo endereço na lista de endereços de
 * clientes.
 *
 * @param	client_addr
 *
 * @return	void
 *****************************************************************************/
void add_client_address(struct sockaddr_in client_addr);

/******************************************************************************
 * Método responsável por remover um endereço de cliente na lista de endreços
 * de clientes.
 *
 * @param	client_addr
 *
 * @return	void
 *****************************************************************************/
void remove_client_address(struct sockaddr_in client_addr);

/******************************************************************************
 * Função responsável por enviar uma mensagem para todos da lista de clientes.
 *
 * @param	message
 * @param	sock_fd
 *
 * @return	void
 *****************************************************************************/
void send_message_broadcast(struct Message message, int sock_fd);


#endif //MULTI_USER_SOCKETS_CHAT_CLIENT_H
