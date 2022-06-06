#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int request_socket, response_socket;
void int_handel (int sig){
        printf("\n Exit from server .....\n");
        close(response_socket);
	close(request_socket);
        exit(0);
}

int main (int argc, char *argv[]){
	signal(SIGINT, int_handel);
	// Creating a file descriptor(socket) which is only meant for the request.
	// socket(family, type, protocol);
	// return type: an integer value; if non negetive value (success) else (failed).
	
	request_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (request_socket > 0){
		printf("Socket creation successful !!\n");
	}
	else{
		printf("Socket creation failed !!\n");
		exit(0);
	}

	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(0);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int len = sizeof(struct sockaddr_in);
	
	// bind function bind the socket to the server..
	// arguements: (file descriptor, server's_address, sizeof_server)
	// return type: int 
        if (bind(request_socket, (struct sockaddr *)&server, sizeof(server)) == 0){
                printf("Socket binding successful !!\n");
        }
        else{
                printf("Socket binding failed !!\n");
                exit(0);
        }
	
        getsockname(request_socket, (struct sockaddr *)&server, &len);
	printf("After bind ephemeral port = %d\n", (int)ntohs(server.sin_port));
	
	// listen function creates a buffer in the server side to store the requests..
	// arguements: (file descriptor, sizeofthebuffer)
	// return type: int
        if (listen(request_socket, 5) == 0){
                printf("Buffer has been created in the server to accept request !!\n");
        }
        else{
                printf("Listen failed !!\n");
                exit(0);
        }

	char data[200];
	char buffer[100];
	int client_size = sizeof(struct sockaddr);
	int n;

	while (1){
	// accept function is used to accept connection request from the client..
	// arguements: (file descriptor, addressofclient, sizeofclient)
	// return type: int
		response_socket = accept(request_socket, (struct sockaddr *)&client, &client_size);
		if (fork() == 0){
			close(request_socket);
			while (1){
				n = recv(response_socket, data, 200, 0);
				if (n == 0){
					break;
				}
				data[n] = '\0';
				printf("\nip: %s, port: %d, Client's reply: %s",inet_ntoa(client.sin_addr), ntohs(client.sin_port), data);
				printf("\n");
				printf("Enter: ");
				scanf("%s", buffer);
				write(response_socket, buffer, sizeof(buffer));
			}
			getpeername(response_socket, (struct sockaddr *) &client, &client_size);
			//printf("\n%s is the ip exiting... \n", inet_ntoa(client.sin_addr));
			//printf("%d is the port of client \n", ntohs(client.sin_port));
			close(response_socket);
			exit(0);
		}
	}
	return 0;
}
