#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	int unsocket = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (unsocket < 0){
		perror("Socket creation failed...: \n");
	}
	else{
		printf("Socket creation successful... \n");
	}
	
	struct sockaddr_un serveraddress;
	memset(&serveraddress, 0, sizeof(struct sockaddr_un));
	serveraddress.sun_family = AF_LOCAL;
	strcpy(serveraddress.sun_path, argv[1]);

	connect(unsocket, (struct sockaddr *) &serveraddress, sizeof(struct sockaddr_un));
	
	int n;
	char buffer[200];
	while (fgets(buffer, 200, stdin) != NULL){
		write(unsocket, buffer, strlen(buffer));
		n = read(unsocket, buffer, 200);
		if (n == 0){
			printf("The server terminated the connection... \n");
			break;
		}
		if (n < 0){
			perror("Read failed...: \n");
		}
		if (n > 0){
			buffer[n] = '\0';
			printf("Server returned: %s\n", buffer);
		}
	}
	close(unsocket);
	return 0;
}
