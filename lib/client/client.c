/******************************************************************************
 * Implementação do gerenciamento de clientes conectados ao servidor          *
 *                                                                            *
 * File:    client.c                                                          *
 * Author:  Samuel Terra Vieira                                               *
 * Address: Universidade Federal de Lavras                                    *
 * Date:    Out/2019                                                          *
 *****************************************************************************/

#include "client.h"

/******************************************************************************
 * Variáveis globais de controle da lista de usuários.
 *****************************************************************************/
struct sockaddr_in client_addresses[MAX_CLIENTS] = {0};
unsigned char clients_control[MAX_CLIENTS] = {0};

/******************************************************************************
 * Função reponsável por verificar se já existe endereço de um cliente na lista
 * de clientes.
 *
 * @param	client_addr
 *
 * @return	Retorna booleando informando a existância do endereço do cliente.
 *****************************************************************************/
int exists_client_address(struct sockaddr_in client_addr) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (memcmp(&client_addresses[i], &client_addr, sizeof(client_addr)) == 0
			&& clients_control[i] == 1) {
			return TRUE;
		}
	}
	return FALSE;
}

/******************************************************************************
 * Função responsável por retornar a primeira posição vazia para adicionar o
 * cliente.
 *
 * @param	void
 *
 * @return	A posição disponivel.
 *****************************************************************************/
int get_position_to_add_client(void) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients_control[i] == 0) {
			return i;
		}
	}
	return -1;
}

/******************************************************************************
 * Função responsável por obter a posição atual de um endereço de um cliente na
 * lista de controle de clientes.
 *
 * @param	client_addr
 *
 * @return	Retorna a posição atual de um endereço na lista de controle.
 *****************************************************************************/
int get_current_position_of_client(struct sockaddr_in client_addr) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (memcmp(&client_addresses[i], &client_addr, sizeof(client_addr)) == 0
			&& clients_control[i] == 1) {
			return i;
		}
	}
	return -1;
}

/******************************************************************************
 * Método responsável por adicionar um novo endereço na lista de endereços de
 * clientes.
 *
 * @param	client_addr
 *
 * @return	void
 *****************************************************************************/
void add_client_address(struct sockaddr_in client_addr) {
	if (!exists_client_address(client_addr)) {
		int position = get_position_to_add_client();
		if (position != -1) {
			memcpy(&client_addresses[position], &client_addr, sizeof(struct sockaddr_in));
			clients_control[position] = 1;
		} else {
			printf("Sala cheia\n");
		}
	}
}

/******************************************************************************
 * Método responsável por remover um endereço de cliente na lista de endreços
 * de clientes.
 *
 * @param	client_addr
 *
 * @return	void
 *****************************************************************************/
void remove_client_address(struct sockaddr_in client_addr) {
	int client_position = get_current_position_of_client(client_addr);
	if (client_position != -1) {
		memset(&client_addresses[client_position], 0, sizeof(struct sockaddr_in));
		clients_control[client_position] = 0;
	}
}

/******************************************************************************
 * Função responsável por enviar uma mensagem para todos da lista de clientes.
 *
 * @param	message
 * @param	sock_fd
 *
 * @return	void
 *****************************************************************************/
void send_message_broadcast(struct Message message, int sock_fd) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients_control[i] == 1) {
			sendto(sock_fd, (struct Message *) &message, sizeof(struct Message), MSG_CONFIRM,
				   (const struct sockaddr *) &client_addresses[i], sizeof(client_addresses[i]));
		}
	}
}
