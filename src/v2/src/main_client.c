#include "client.h"

int main() {

  int client_fd = open_client_fd("127.0.0.1", "29008");
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