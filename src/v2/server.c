#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LISTENQ 10
#define HOSTNAME_SIZE 2048
#define PORT_SIZE 64

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

int main() {
  int listenfd, connfd;

  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  char client_hostname[HOSTNAME_SIZE], client_port[PORT_SIZE];
  char *message_to_client = "HTTP/1.1 200 OK\nContent-Type: "
                            "text/plain\nContent-Length: 12\n\nHello world!";

  listenfd = open_listen_fd("29008");
  while (1) {
    printf("Server waiting\n\n");
    clientlen = sizeof(struct sockaddr_storage);

    if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr,
                         (socklen_t *)&clientlen)) < 0) {
      perror("In accept");
      exit(EXIT_FAILURE);
    }

    Getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname,
                HOSTNAME_SIZE, client_port, PORT_SIZE, 0);
    printf("Connected to (%s, %s)\n", client_hostname, client_port);

    char buffer[30000] = {0};
    read(connfd, buffer, 30000);
    printf("%s\n", buffer);
    write(connfd, message_to_client, strlen(message_to_client));
  }
  return 0;
}
