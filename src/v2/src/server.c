#include "server.h"

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