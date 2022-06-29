#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/signal.h>

int main (){
	signal (SIGCHLD, SIG_IGN);
	int socket;
	socket = socket(AF_INET, SOCK_STREAM, 0);
	if (socket < 0){
		perror("Socket creation failed...: \n");
	}
	else{
		printf("Socket creation successful... \n");
	}
	struct sockaddr_in serveraddr;
	serveraddr.sin_port = htons(33456);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int br = bind(socket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (br < 0){
		perror("Binding failed...: \n");
	}
	else{
		printf("Binding successful... \n");
	}

	int lr = listen(socket, 10);
	if (lr < 0){
		perror("Listen failed...: \n");
	}
	else{
		printf("Listen successful... \n");
		len = sizeof(struct sockaddr_in);
		getsockname(socket, (struct sockaddr *)&serveraddr, &len);
		print("Server ip: %s\n", inet_ntoa(serveraddr.sin_addr));
		printf("Server is listening on: %d\n", ntohs(serveraddr.sin_port));
	}

	int fd;
	struct sockaddr_in clientaddress;
	while (1){
		len = sizeof(struct sockaddr_in);
		fd = accept(socket, (struct sockaddr *)&clientaddress, &len);
		if (fd < 0){
			perror("Accept failed...: \n");
		}
		else{
			printf("Server is currently accepting... \n");
			len = sizeof(struct sockaddr_in);
			getsockname(fd, (struct sockaddr *)&clientaddress, &len);
			print("Local ip: %s\n", inet_ntoa(clientaddress.sin_addr));
            printf("Local port: %d\n", ntohs(clientaddress.sin_port));

			len = sizeof(struct sockaddr_in);
			getpeername(fd, (struct sockaddr *)&clientaddress, &len);
			print("Remote ip: %s\n", inet_ntoa(clientaddress.sin_addr));
            printf("Remote port: %d\n", ntohs(clientaddress.sin_port));
		}
		pid_t pid = fork();
		if (pid < 0){
			perror("Fork failed...: \n");
		}
		else if (pid == 0){
			close(socket);
		}
		char buffer[200];
		int n;
		while(1){
			n = read(fd, buffer, 199);
			if (n == 0){
				printf("Client terminated... \n");
			}
			else{
				write(fd, buffer, strlen(buffer));
			}
			exit(0);
		}
		else{
			close(fd);
		}
	}
	return 0;
}
