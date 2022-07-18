#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[]){
	int unsocket = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (unsocket < 0){
		perror("Socket creation failed...: \n");
	}
	else{
		printf("Socket creation successful... \n");
	}

	struct sockaddr_un serveraddress, server_temp;
	memset(&serveraddress, 0, sizeof(struct sockaddr_un));
	serveraddress.sun_family = AF_LOCAL;
	strcpy(serveraddress.sun_path, argv[1]);
	
	unlink(argv[1]);

	int br = bind(unsocket, (struct sockaddr *) &serveraddress, sizeof(struct sockaddr_un));
	if (br < 0){
		perror("Binding failed...: \n");
	}
	else{
		printf("Binding successful... \n");
		int len = sizeof(struct sockaddr_un);
		getsockname(unsocket, (struct sockaddr *)&server_temp, &len);
		printf("Binding path: %s, length returned: %d\n", server_temp.sun_path, len);
	}
	close(unsocket);
	return 0;
}
