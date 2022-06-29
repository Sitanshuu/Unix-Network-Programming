#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

int main (int argc, char *argv[]){
	int netsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (netsocket < 0){
		perror("Socket failed...: \n");
	}
	else{
		printf("Socket creation successful... \n");
	}

	struct sockaddr_in s_addr, sa, ca;
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(argv[2]));
	s_addr.sin_addr.s_addr = inet_addr(argv[1]);

	int len = sizeof(struct sockaddr_in);
	int br = connect(netsocket, (struct sockaddr *)&s_addr, len);
	if (br < 0){
		perror("Connection failed...: \n");
	}
	else{
		printf("Connection successful... \n");
		len = sizeof(struct sockaddr_in);
		getsockname(netsocket, (struct sockaddr *)&ca, &len);
		printf("Client ip: %s\n", inet_ntoa(ca.sin_addr));
		printf("Client port: %d\n", ntohs(ca.sin_port));

		len = sizeof(struct sockaddr_in);
        getsockname(netsocket, (struct sockaddr *)&sa, &len);
        printf("Server ip: %s\n", inet_ntoa(sa.sin_addr));
        printf("Server port: %d\n", ntohs(sa.sin_port));
	}
	int n;
	char buffer[200];
	struct pollfd fds[2];

	while (1){
		fds[0].fd = fileno(stdin);
		fds[0].events = POLLRDNORM;
		fds[1].fd = netsocket;
		fds[1].events = POLLRDNORM;
		poll(fds, 2, -1);

		if (fds[0].revents & POLLRDNORM){
			if (fgets(buffer, 200, stdin) == NULL){
				printf("User finished... \n");
				exit(0);
			}
			else{
				write(netsocket, buffer, strlen(buffer));
			}
		}
		if (fds[1].revents & POLLRDNORM){
			n = read(netsocket, buffer, 200);
			if (n == 0){
				printf("FIN has been received... \n");
				exit(0);
			}
			else{
				buffer[n] = '\0';
				printf("Received from the server: %s\n", buffer);
			}
		}
	}
	return 0;
}
