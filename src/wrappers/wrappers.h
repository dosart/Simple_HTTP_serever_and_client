#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

int Socket(int domain, int type, int protocol);

int Connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int listenfd, struct sockaddr *addr, int *addrlen);

int Getaddrinfo(const char *host, const char *service,
                const struct addrinfo *hints, struct addrinfo **result);

void Freeaddrinfo(struct addrinfo *result);

#endif