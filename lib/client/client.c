#include "client.h"

struct sockaddr_in client_addresses[MAX_CLIENTS] = {0};
unsigned char clients_control[MAX_CLIENTS] = {0};

int exists_client_address(struct sockaddr_in client_addr) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (memcmp(&client_addresses[i], &client_addr, sizeof(client_addr)) == 0
			&& clients_control[i] == 1) {
			return TRUE;
		}
	}
	return FALSE;
}

// return the first position to add a client
int get_position_to_add_client() {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients_control[i] == 0) {
			return i;
		}
	}
	return -1;
}

int get_current_position_of_client(struct sockaddr_in client_addr) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (memcmp(&client_addresses[i], &client_addr, sizeof(client_addr)) == 0
			&& clients_control[i] == 1) {
			return i;
		}
	}
	return -1;
}

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

void remove_client_address(struct sockaddr_in client_addr) {
	int client_position = get_current_position_of_client(client_addr);
	if (client_position != -1) {
		memset(&client_addresses[client_position], 0, sizeof(struct sockaddr_in));
		clients_control[client_position] = 0;
	}
}

void send_message_broadcast(struct Message message, int sock_fd) {
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients_control[i] == 1) {
			sendto(sock_fd, (struct Message *) &message, sizeof(struct Message), MSG_CONFIRM,
				   (const struct sockaddr *) &client_addresses[i], sizeof(client_addresses[i]));
		}
	}
}
