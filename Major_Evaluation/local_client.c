#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

// signal(signal_id, function_name)
int net_socket;
void int_handel (int sig){
	printf("\n Exit from client .....\n");
	close(net_socket);
	exit(0);
}

int main (int argc, char *argv[]){

	signal(SIGINT, int_handel);
	// create socket
	net_socket = socket (AF_INET, SOCK_STREAM, 0);
	
	// connect to server
	// define address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	// call connect function
	connect(net_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	
	//recv data
	char data[201];
        int n;
	char buffer[5];
        while(1)
        {
                printf("\nEnter : ");
                scanf("%s", buffer);
                write(net_socket, buffer, strlen(buffer));
                n = recv(net_socket, data, 200, 0);
                data[n] = '\0';
                printf("ip: %s, port: %d, Server's Reply: %s\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port), data);
        }
        //close the connection
        close(net_socket);
        return(0);
}
