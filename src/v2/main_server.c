#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LISTENQ 10
#define CLIENT_HOSTNAME_SIZE 2048
#define CLIENT_PORT_SIZE 64
#define MESSAGE_FROM_CLIENT_LEN 4096

void set_empty(char *str, size_t str_size) { memset(str, '\0', str_size); }

int main() {
  socklen_t client_len;
  struct sockaddr_storage client_addr;

  char client_hostname[CLIENT_HOSTNAME_SIZE], client_port[CLIENT_PORT_SIZE];
  char *message_to_client = "HTTP/1.1 200 OK\nContent-Type: "
                            "text/plain\nContent-Length: 12\n\nHello world!";
  size_t message_to_client_len = strlen(message_to_client);
  char message_from_client[MESSAGE_FROM_CLIENT_LEN] = {0};

  int listen_fd, client_fd;
  listen_fd = Open_listen_fd("29008", 10);
  while (1) {
    printf("Server waiting\n\n");
    client_len = sizeof(struct sockaddr_storage);

    if ((client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                            (socklen_t *)&client_len)) < 0) {
      errno = client_fd;
      perror("accept");
    }

    Getnameinfo((struct sockaddr *)&client_addr, client_len, client_hostname,
                CLIENT_HOSTNAME_SIZE, client_port, CLIENT_PORT_SIZE, 0);
    printf("Connected to (%s, %s)\n", client_hostname, client_port);

    Recv(client_fd, message_from_client, MESSAGE_FROM_CLIENT_LEN, 0);
    printf("%s\n", message_from_client);
    Send(client_fd, message_to_client, message_to_client_len, 0);

    set_empty(message_from_client, MESSAGE_FROM_CLIENT_LEN);
    set_empty(client_hostname, CLIENT_HOSTNAME_SIZE);
    set_empty(client_port, CLIENT_PORT_SIZE);
  }
  return 0;
}
