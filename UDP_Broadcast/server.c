#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0){
		perror("Socket creation failed...: \n");
	}
	else{
		printf("Socket creation successful... \n");
	}

	int val = 0;
	int val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_BROADCAST, &val, &val_len);
	
	if (val == 1){
		printf("Broadcast is allowed... \n");
	}
	else{
		printf("UDP broadcast is not allowed... \n");
		printf("Setting the broadcast option to 1... \n");
		val = 1;
		setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));
	}
	
	val = 0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_BROADCAST, &val, &val_len);
    	
	if (val == 1){
        	printf("Now UDP broadcast is allowed after setting the broadcast option to 1... \n");
    	}

	struct sockaddr_in clientaddress;
	clientaddress.sin_family = AF_INET;
	clientaddress.sin_port = htons(atoi(argv[2]));
	clientaddress.sin_addr.s_addr = inet_addr(argv[1]);

    	char buffer[200];
	int str;
	printf("Enter message to broadcast: ");
	while (fgets(buffer, 200, stdin) != NULL){
		printf("Enter message to broadcast: ");
		str = sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr *) &clientaddress, sizeof(struct sockaddr_in));
		printf("Sendto: %d\n", str);
		
		/*
		if (n != NULL){
			sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr *) &clientaddress, sizeof(struct sockaddr_in));
		}
		else{
			printf("The program is terminated due to no availability of the data... \n");
			exit(0);
		}
		*/
	}
	close(fd);
	return 0;
}
