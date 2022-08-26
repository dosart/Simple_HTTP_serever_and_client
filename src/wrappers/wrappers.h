#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);

int Connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int listenfd, struct sockaddr *addr, int *addrlen);

#endif