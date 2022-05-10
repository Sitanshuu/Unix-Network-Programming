#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char * argv[]){
	int request_socket;
	request_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(5600);
	server.sin_addr.s_addr = inet_addr(argv[1]);

	bind(request_socket, (struct sockaddr *) &server, sizeof(server));

	listen(request_socket, 10);

	int response_socket;
	struct sockaddr_in client;
	int client_size;
	char data[200];
	while (1){
		response_socket = accept(request_socket, (struct sockaddr *) &client, &client_size);
		write(response_socket, data, strlen(data));
		close(response_socket);
	}

	return 0;
}
