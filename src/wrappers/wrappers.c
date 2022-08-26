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

int Accept(int listenfd, struct sockaddr *addr, int *addrlen) {
  int status = accept(listenfd, addr, addrlen);
  if (status != 0) {
    errno = status;
    perror("accept");
    return -1;
  }
  return status;
}