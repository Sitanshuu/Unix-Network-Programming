#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main (int argc, char *argv[]){

	// Create a socket..
	int net_socket;
	net_socket = socket (AF_INET, SOCK_STREAM, 0);
	
	// Store the server details..
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(5600);
	server.sin_addr.s_addr = inet_addr(argv[1]);

	// Connect to the server..
	connect(net_socket, (struct sockaddr *) &server, sizeof(server));

	// Read, write operations..
	char data[200];
	int n;
	n = recv(net_socket, data, 200, 0);
	printf("Reply from the Server: %s\n", data);
	
	// Closing the file descriptor..
	close(net_socket);
	
	return 0;
}
