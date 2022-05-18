#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[]){
    
    // Creating a socket..
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Storing the details of the server which is going to get connected..
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = inet_addr(argv[1]);
    
    // Connect to the server..
    connect(net_socket, (struct sockaddr *) &server, sizeof(server));
    
    // Write, read operations..
    char data[200];
    int n;
    char buffer[5];
    while (1){
	    printf("Enter text: ");
	    scanf("%s", buffer);
	    write(net_socket, buffer, strlen(buffer));
            n = recv(net_socket, data, 200, 0);
            data[n] = '\0';
            printf("Reply: %s\n", data);
    }    
    return 0;
}

