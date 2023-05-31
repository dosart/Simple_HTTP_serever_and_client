#include "wrappers.h"

int Socket(int domain, int type, int protocol) {
  int status = socket(domain, type, protocol);
  if (status != 0) {
    errno = status;
    perror("socket");
    return -1;
  }
  return status;
}

int Connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen) {
  int status = connect(clientfd, addr, addrlen);
  if (status != 0) {
    errno = status;
    perror("connect");
    return -1;
  }
  return status;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int status = bind(sockfd, addr, addrlen);
  if (status != 0) {
    errno = status;
    perror("bind");
    return -1;
  }
  return status;
}

int Listen(int sockfd, int backlog) {
  int status = listen(sockfd, backlog);
  if (status != 0) {
    errno = status;
    perror("listen");
    return -1;
  }
  return status;
}

int Accept(int listenfd, struct sockaddr *addr, socklen_t *addrlen) {
  int status = accept(listenfd, addr, addrlen);
  if (status != 0) {
    errno = status;
    perror("accept");
    return -1;
  }
  return status;
}

int Getaddrinfo(const char *host, const char *service,
                const struct addrinfo *hints, struct addrinfo **result) {
  int status = getaddrinfo(host, service, hints, result);
  if (status != 0) {
    errno = status;
    perror("getaddrinfo");
    return -1;
  }
  return status;
}

void Freeaddrinfo(struct addrinfo *result) { freeaddrinfo(result); }

int Setsockopt(int s, int level, int optname, const void *optval,
               socklen_t optlen) {
  int status = setsockopt(s, level, optname, optval, optlen);
  if (status != 0) {
    errno = status;
    perror("setsockopt");
    return -1;
  }
  return status;
}

int Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host,
                socklen_t hostlen, char *serv, socklen_t servlen, int flags) {
  int status = getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
  if (status != 0) {
    errno = status;
    perror("getnameinfo");
    return -1;
  }
  return status;
}

ssize_t Send(int sockfd, const void *msg, size_t len, int flags) {
  ssize_t status = send(sockfd, msg, len, flags);
  if (status == -1) {
    perror("send");
    return -1;
  }
  return status;
}

ssize_t Recv(int sockfd, void *buf, size_t len, int flags) {
  ssize_t status = recv(sockfd, buf, len, flags);
  if (status == -1) {
    perror("recv");
    return -1;
  }
  return status;
}

int Open_listen_fd(const char *port, int listen_size) {
  int listen_fd = open_listen_fd(port, listen_size);
  if (listen_fd == -1) {
    errno = listen_fd;
    perror("open_listen_fd");
    return -1;
  }
  return listen_fd;
}

int open_listen_fd(const char *port, int listen_size) {

  struct addrinfo hints, *results, *p;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;  // TCP socket
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

  if (listen(listen_fd, listen_size) < 0) {
    close(listen_fd);
    return -1;
  }

  return listen_fd;
}

int Open_client_fd(char *host_name, char *port) {
  int client_fd = open_client_fd(host_name, port);
  if (client_fd == -1) {
    errno = client_fd;
    perror("open_client_fd");
    return -1;
  }
  return client_fd;
}

int open_client_fd(char *hostname, char *port) {
  struct addrinfo hints, *results, *p;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM; // TCP socket
  hints.ai_flags = AI_NUMERICSERV; // Port is number
  hints.ai_flags |= AI_ADDRCONFIG;
  Getaddrinfo(hostname, port, &hints, &results);

  int client_fd;
  // Find socket using hints. add socket to list of results
  for (p = results; p; p = p->ai_next) {
    if ((client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
      continue; // Bad luck. Try next address

    if (connect(client_fd, p->ai_addr, p->ai_addrlen) != -1)
      break;          // It's luck.

    close(client_fd); // Bad luck. Close the socket
  }
  Freeaddrinfo(results);

  if (p == NULL) // All address is wrong
    return -1;
  else
    return client_fd;
}