#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	int val = 1, val_len = sizeof(int);
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &val, val_len);

	struct sockaddr_in ownaddress;
	ownaddress.sin_family = AF_INET;
	ownaddress.sin_port = htons(33456);
	ownaddress.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(fd, (struct sockaddr *)&ownaddress, sizeof(struct sockaddr_in));

	struct sockaddr_in serveraddress;
	int len = sizeof(struct sockaddr_in);
	char buffer[200];
	while (1){
		int n = recvfrom(fd, buffer, 200, 0, (struct sockaddr *)&serveraddress, &len);
		if (n < 0){
			perror("Read failed... \n");
		}
		else if (n == 0){
			break;
		}
		else{
			if (buffer[0] == "\n"){
				close(fd);
				printf("The program is terminating as there is no data in the buffer... \n");
				exit(0);
			}
			else{
				buffer[n] = '\0';
				printf("The broadcasting reply is: %s\n", buffer);
			}
		}
	}
	close(fd);
	return 0;
}
