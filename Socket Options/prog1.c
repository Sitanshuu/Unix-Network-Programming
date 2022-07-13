#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

int main (){
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	int val, val_len;
	printf("==================== BEFORE SETSOCKOPT ==================== \n");
	val = 0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, &val_len);
	printf("The default value of the send buffer size in TCP is: %d\n", val);

	val = 0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, &val_len);
	printf("The default value of the receive buffer size in TCP is: %d\n", val);

	val = 1;
	setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, sizeof(val));
	val = 1;
	setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, sizeof(val));
    printf("==================== AFTER SETSOCKOPT ==================== \n");
	val = 0;
    val_len = sizeof(val);
    getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, &val_len);
    printf("The default value of the send buffer size in TCP is: %d\n", val);
   
    val = 0;
    val_len = sizeof(val);
    getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, &val_len);
    printf("The default value of the receive buffer size in TCP is: %d\n", val);

	close(fd);
	printf("\n");

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	val = 0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, &val_len);
	printf("The default value of the send buffer size in UDP is: %d\n", val);

	val = 0;
	val_len = sizeof(val);
	getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, &val_len);
	printf("The default value of the receive buffer in UDP is: %d\n", val);
}
