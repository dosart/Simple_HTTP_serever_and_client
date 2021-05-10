// Client side C program to demonstrate Socket programming
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int client_fd = 0;
  if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket create error");
    exit(EXIT_FAILURE);
  }

  const uint16_t port = 8080;

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  memset(server_address.sin_zero, 0, sizeof(server_address.sin_zero));

  if (connect(client_fd, (struct sockaddr *)&server_address,
              sizeof(server_address)) < 0) {
    perror("connect error");
    exit(EXIT_FAILURE);
  }

  char *message = "Hello from client";
  send(client_fd, message, strlen(message), 0);
  
  char buffer[2048] = {0};
  recv(client_fd, buffer, 2048, 0);
  
  printf("Message from server: %s\n", buffer);

  close(client_fd);
  return 0;
}
