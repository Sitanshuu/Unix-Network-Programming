#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main (){
	int usocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (usocket < 0){
		perror("Socket creation failed...: \n");
	}
	else{
		printf("Socket creation successful... \n");
	}

	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(56789);
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);

	int len = sizeof(struct sockaddr_in);
	int br = bind(usocket, (struct sockaddr *)&serveraddress, len);
	if (br < 0){
		perror("Binding failed...: \n");
	}
	else{
		printf("Binding successful... \n");
		len = sizeof(struct sockaddr_in);
		getsockname(usocket, (struct sockaddr *)&serveraddress, &len);
		printf("Server ip: %s\n", inet_ntoa(serveraddress.sin_addr));
		printf("Server port: %d\n", ntohs(serveraddress.sin_port));
	}
	char buffer[200];
	int n;
	struct sockaddr_in ca;

	while (1){
		// n = read(usocket, buffer, 200);
		len = sizeof(struct sockaddr_in);
		n = recvfrom(usocket, buffer, 200, 0, (struct sockaddr *)&ca, &len);
		if (n < 0){
			perror("Read failed...: \n");
		}
		else if (n == 0){
			break;
		}
		else{
		printf("Read complete... \n");
		buffer[n] = '\0';
		// n = write(usocket, buffer, strlen(buffer));
		n = sendto(usocket, buffer, strlen(buffer), 0, (struct sockaddr *)&ca, len);
		if (n < 0){
		perror("Write failed...: \n");
		}
		}
	}
	close(usocket);
	return 0;
}
