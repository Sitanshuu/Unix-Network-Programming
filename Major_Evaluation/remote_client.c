#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include<signal.h>

//#define PORT 4444

int remoteClientSocket;

void int_handle(int sig)
{
	printf("[-]Disconnected from server.\n");
	close(remoteClientSocket);
	exit(0);
}

int main(int argc, char *argv[]){
	signal(SIGINT, int_handle);
	remoteClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	char buffer[1024];

	if(remoteClientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Remote Client Socket is created.\n");
	
	struct sockaddr_in serverAddr;
	//memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	int con;
	con = connect(remoteClientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(con < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		printf("Remote Client: \t");
		scanf("%s", &buffer[0]);
		send(remoteClientSocket, buffer, strlen(buffer), 0);

		/*if(strcmp(buffer, ":exit") == 0){
			close(localClientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}*/

		if(recv(remoteClientSocket, buffer, 1024, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("ip: %s, port: %d, Chat Server: %s\n",inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port), buffer);
		}
	}

	return 0;
}
