#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main (int argc, char *argv[]){

	// Create a socket..
	
	int net_socket;
	net_socket = socket (AF_INET, SOCK_STREAM, 0);      // IPV4, CONNECTION, PROTOCOL; RETURN TYPE: INT
	
	// Store the server details..
	
	struct sockaddr_in server;
	server.sin_family = AF_INET;       // Family of the server.
	server.sin_port = htons(5600);       // Port number of the server.
	server.sin_addr.s_addr = inet_addr(argv[1]);   // ip address of the server.

	// Connect to the server..
	
	connect(net_socket, (struct sockaddr *) &server, sizeof(server));  // Socket(file name), , size.

	char data[201];
	int n;
	n = recv(net_socket, data, 200, 0);

	printf("Reply from the Server: %s\n", data);
	
	// Closing the file descriptor..
	
	close(net_socket);
	return 0;

}
