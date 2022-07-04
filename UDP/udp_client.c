#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[]){
	int usocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (usocket < 0){
		perror("Socket creation failed...: \n");
	}
	else{
		printf("Socket creation successful... \n");
	}

	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(atoi(argv[2]));
	serveraddress.sin_addr.s_addr = inet_addr(argv[1]);

	int n;
	char buffer[200];
	int len;
	len = sizeof(struct sockaddr_in);
	// int cr = connect(usocket, (struct sockaddr *)&serveraddress, len);

	while (fgets(buffer, 200, stdin) != NULL){
		// n = write(usocket, buffer, strlen(buffer));
		n = sendto(usocket, buffer, strlen(buffer), 0, (struct sockaddr *)&serveraddress, len);
		if (n < 0){
			perror("Write failed...: \n");
		}
		else{
			// n = read(usocket, buffer, 200);
			n = recvfrom(usocket, buffer, 200, 0, (struct sockaddr *)&serveraddress, &len);
			if (n < 0){
				perror("Read failed...: \n");
			}
			else{
				buffer[n] = '\0';
				printf("Reply: %s\n", buffer);
			}
		}
	}
	close(usocket);
	return 0;
}
