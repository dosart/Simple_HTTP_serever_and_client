#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LISTENQ 10
#define CLIENT_HOSTNAME_SIZE 2048
#define CLIENT_PORT_SIZE 64
#define MESSAGE_FROM_CLIENT_LEN 4096

int open_listen_fd(char *port) {

  struct addrinfo hints, *results, *p;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM; // TCP socket
  hints.ai_flags =
      AI_PASSIVE | AI_ADDRCONFIG;   // Write my IP and use IPv4 or IPv6
  hints.ai_flags |= AI_NUMERICSERV; // Port is number

  int listen_fd, optval = 1;

  // Find socket using hints. add socket to list of results
  Getaddrinfo(NULL, port, &hints, &results);
  for (p = results; p != NULL; p = p->ai_next) {
    if ((listen_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
      continue; // Bad luck. Try next address

    /* Prevent "Address already in use" error */
    Setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
               sizeof(int));

    if (bind(listen_fd, p->ai_addr, p->ai_addrlen) == 0)
      break; // It's luck.

    close(listen_fd);
  }
  Freeaddrinfo(results);

  if (p == NULL) // All address is wrong
    return -1;

  if (listen(listen_fd, LISTENQ) < 0) {
    close(listen_fd);
    return -1;
  }

  return listen_fd;
}

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
  listen_fd = open_listen_fd("29008");
  while (1) {
    printf("Server waiting\n\n");
    client_len = sizeof(struct sockaddr_storage);

    if ((client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                            (socklen_t *)&client_len)) < 0) {
      perror("In accept");
      exit(EXIT_FAILURE);
    }

    Getnameinfo((struct sockaddr *)&client_addr, client_len, client_hostname,
                CLIENT_HOSTNAME_SIZE, client_port, CLIENT_PORT_SIZE, 0);
    printf("Connected to (%s, %s)\n", client_hostname, client_port);

    recv(client_fd, message_from_client, MESSAGE_FROM_CLIENT_LEN, 0);
    printf("%s\n", message_from_client);
    send(client_fd, message_to_client, message_to_client_len, 0);

    set_empty(message_from_client, MESSAGE_FROM_CLIENT_LEN);
    set_empty(client_hostname, CLIENT_HOSTNAME_SIZE);
    set_empty(client_port, CLIENT_PORT_SIZE);
  }
  return 0;
}
