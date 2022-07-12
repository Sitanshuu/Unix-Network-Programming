#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_ip_port (int usocket){
	struct sockaddr_in ca, sa;
	int len = sizeof(struct sockaddr_in);
	getsockname(usocket, (struct sockaddr *)&ca, &len);
	printf("Client ip: %s\n", inet_ntoa(ca.sin_addr));
	printf("Client is running on port: %d\n", ntohs(ca.sin_port));

	len = sizeof(struct sockaddr_in);
	getpeername(usocket, (struct sockaddr *)&sa, &len);
	printf("Server ip: %s\n", inet_ntoa(sa.sin_addr));
	printf("Server is running on port: %d\n", ntohs(sa.sin_port));
}

int main (){
	int lsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (lsocket < 0){
		perror("Socket creation failed...: \n");
	}
	else{
		printf("Socket creation successful...: \n");
	}

	printf("\n********** Before Binding **********\n");
	print_ip_port(lsocket);

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(33564);
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	len = sizeof(struct sockaddr_in);
	int br = bind(lsocket, (struct sockaddr *) &serv_addr, len);
	if (br < 0){
		perror("Binding failed...: \n");
	}
	else{
		printf("Binding successful... \n");
	}

	printf("\n********** After Binding **********\n");
    print_ip_port(lsocket);

	int lr = listen(lsocket, 256);
	if (lr < 0){
		perror("Listening failed...: \n");
	}
	else{
		printf("Listen successful... \n");
	}

	int afds[256];
	for (int i=0; i<256; i++){
		afds[i] = -1;
	}
	fd_set read_set;
	FD_ZERO(&read_set);
	FD_SET(lsocket, &read_set);
	int fd, maxfds = lsocket + 1, n;
	char buffer[200];
	struct sockaddr_in ca;

	while (1){
		select(maxfds, &read_set, NULL, NULL, NULL);
		if (FD_ISSET(lsocket, &read_set)){
			len = sizeof(struct sockaddr_in);
			fd = accept(lsocket, (struct sockaddr *)&ca, &len);
			for (int i=0; i<256; i++){
				if (afds[i] == -1){
					break;
				}
				else if (i == 256){
					printf("Max server capacity reached... \n");
					continue;
				}
				else{
					afds[i] = fd;
					if (maxfds < fd){
						maxfds = fd;
					}
					else{
						FD_SET(fd, &read_set);
					}
				}
				for (int i=0; i<256; i++){
					if (afds[i] == -1){
						continue;
					}
					else{
						if (FD_ISSET(afds[i], &read_set)){
							n = read(afds[i], buffer, 200);
							if (n < 0){
								perror("Read failed...: \n");
							}
							else if (n == 0){
								close(afds[i]);
								FD_CLR(afds[i], &read_set);
								afds[i] = -1;
							}
							else{
								buffer[n] = '\0';
								write(afds[i], buffer, strlen(buffer));
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
