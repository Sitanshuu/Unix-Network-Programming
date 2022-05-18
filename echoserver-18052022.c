#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

int main (int argc, char *argv[]){
    
    // Creating a socket..
    int request_socket, response_socket;
    request_socket= socket(AF_INET, SOCK_STREAM, 0);
    
    // Storing the details of the server which is going to get connected..
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(0);
    //server.sin_port = htons(5600);
    //server.sin_addr.s_addr = inet_addr(argv[1]);
    
    // Binding the socket to the port..
    int len = sizeof(struct sockaddr_in); 
    bind(request_socket, (struct sockaddr *) &server, sizeof(server));
    getsockname(request_socket, (struct sockaddr *)&server, &len);
    printf("After bind ephemeral port = %d\n", (int)ntohs(server.sin_port));
    // Listen: create queue to store requests..
    listen(request_socket, 10);
    
    // Read, write operations..
    char data[200];
    int client_size, n;
    
    while (1){
        response_socket = accept(request_socket, (struct sockaddr *) &client, &client_size);
        n = recv(response_socket, data, 200, 0);
        data[n] = '\0';
        write(response_socket, data, strlen(data));
        close(response_socket);
    }   
    return 0;
}
