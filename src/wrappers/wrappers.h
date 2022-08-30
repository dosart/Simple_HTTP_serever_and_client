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
                size_t hostlen, char *serv, size_t servlen, int flags) {
  int status = getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
  if (status != 0) {
    errno = status;
    perror("getnameinfo");
    return -1;
  }
  return status;
}

int Send(int sockfd, const void *msg, int len, int flags) {
  int status = send(sockfd, msg, len, flags);
  if (status == -1) {
    errno = status;
    perror("send");
    return -1;
  }
  return status;
}

int Recv(int sockfd, void *buf, int len, int flags) {
  int status = recv(sockfd, buf, len, flags);
  if (status == -1) {
    errno = status;
    perror("recv");
    return -1;
  }
  return status;
}
