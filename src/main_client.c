#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

  if (argc < 3) {
    printf("Usage: client [ip] [port]\n");
    return 1;
  }

  const char *ip = argv[1];

  const char *str_port = argv[2];
  unsigned long int_port = strtoul(str_port, NULL, 0);
  if (int_port < 1 || int_port > 65535) {
    printf("You must enter a valid port number.\n");
    return 1;
  }

  int client_fd = Open_client_fd(ip, str_port);
  if (client_fd == -1) {
    perror("open_client_fd");
    return -1;
  }
  char *message = "Hello from client";
  Send(client_fd, message, strlen(message), 0);

  char buffer[2048] = {0};
  Recv(client_fd, buffer, 2048, 0);

  printf("Message from server: %s\n", buffer);
  close(client_fd);
}