// Server side C program to demonstrate Socket programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 3425
int main(int argc, char const *argv[]) {

  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket error");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htons(INADDR_ANY);
  address.sin_port = htons(PORT);

  memset(address.sin_zero, 0, sizeof(address.sin_zero));

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
    perror("error bind");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 10) == -1) {
    perror("error listen");
    exit(EXIT_FAILURE);
  }

  int address_len = sizeof(address);
  int client_fd = 0;
  int bytes_read = 0;
  while (1) {
    printf("Server waiting\n\n");
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address,
                            (socklen_t *)&address_len)) == -1) {
      perror("In accept");
      exit(EXIT_FAILURE);
    }

    char buffer[2048] = {0};
    while (1) {
      bytes_read = recv(client_fd, buffer, 2048, 0);
      if (bytes_read <= 0)
        break;
    }
    printf("%s\n", buffer);
    close(client_fd);
  }
  return 0;
}
