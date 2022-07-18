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

	int lr = listen(unsocket, 10);
	int len, n;
	char buffer[200];
	if (lr < 0){
		perror("Listen failed...: \n");
	}
	else{
		printf("Listen successful... \n");

	}
	while (1){
		len = sizeof(struct sockaddr_un);
		int con = accept(unsocket, (struct sockaddr *)&serveraddress, &len);
		if (con < 0){
			perror("Accept failed...: \n");
		}
		else{
			while (1){
				n = read(con, buffer, 200);
				if (n == 0){
					printf("Client closed... \n");
					close(con);
					break;
				}
				if (n < 0){
					perror("Read failed...: \n");
				}
				if (n > 0){
					buffer[n] = '\0';
					n = write(con, buffer, strlen(buffer));
					if (n < 0){
						perror("Writ failed...: \n");
					}
				}
			}
		}
	}
        close(unsocket);
        return 0;
}

