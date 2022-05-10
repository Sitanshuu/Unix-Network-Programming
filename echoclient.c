#include <stdio.h>
#include <sys/socket.h>
#include <arps/inet.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char * argv[]){
	int net_socket;
	net_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(5600);
	server.sin_addr.s_addr = inet_addr(argv[1]);

	connect(net_socket, (struct * sockaddr) &server, sizeof(server));

	char data[200];
	int n;
	write(net_socket, data, strlen(data));
	n = recv(net_socket, data, 200, 0);
	printf("Reply from the server: %s\n", data);
	close(net_socket);

	return 0;
}
