#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main (int argc, char *argv[]){
    
    // Create a socket..
    int request_socket, response_socket;
    request_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Connect to a server where we want to get connected..
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

	// Binding the socket and the port..
    bind(request_socket, (struct sockaddr *) &server_address, sizeof(server_address));
 
	// Listen: create queue to store requests..
    listen(request_socket, 10);
	
	// Read, write operations..
	char data[201];
    int client_size, n;
    char str[100];
    time_t tick;
	
    while (1){
	    response_socket = accept(request_socket, (struct sockaddr *) &client_address, &client_size);
	    printf("Accepted");
	    tick = time(NULL);
	    snprintf(str, sizeof(str), "%s", ctime(&tick));
	    printf("%s", str);
	    write(response_socket, str, strlen(str));
    }

    return 0;
}
