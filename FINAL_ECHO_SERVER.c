#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main (int argc, char * argv[]){
  int request_socket, response_socket;
  request_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(5600);
  server.sin_addr.s_addr = inet_addr(argv[1]);
  
  bind(request_socket, (struct sockaddr *) &server, sizeof(server));
  listen(request_socket, 10);
  
  int n
  while (1){
  }
  return 0;
}
