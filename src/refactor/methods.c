#include "methods.h"
#include "wrappers.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)

void using_simple(int server_fd) {
  struct sockaddr_storage client_addr;
  socklen_t address_len = sizeof(struct sockaddr_storage);
  int client_fd;
  while (1) {
    printf("Server waiting\n\n");
    if ((client_fd = Accept(server_fd, (struct sockaddr *)&client_addr,
                            (socklen_t *)&address_len)) == -1) {
      exit(EXIT_FAILURE);
    }

    char message_from_client[2048] = {0};
    if (Recv(client_fd, message_from_client, 2048, 0) == -1) {
      exit(EXIT_FAILURE);
    }

    printf("Message from client: %s\n", message_from_client);

    if (Send(client_fd, message_from_client, 2048, 0) == -1) {
      exit(EXIT_FAILURE);
    }

    close(client_fd);
  }
}

void sigchld_handler(int sig) {
  UNUSED(sig);
  while (waitpid(-1, 0, WNOHANG) > 0)
    ;

  write(0, "Request is done\n", 16);
  return;
}

void using_fork(int server_fd) {
  struct sockaddr_storage client_addr;
  socklen_t address_len = sizeof(struct sockaddr_storage);
  int client_fd;

  signal(SIGCHLD, sigchld_handler);

  while (1) {
    printf("Server waiting\n\n");

    if ((client_fd = Accept(server_fd, (struct sockaddr *)&client_addr,
                            (socklen_t *)&address_len)) == -1) {
      exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
      close(server_fd);

      char message_from_client[2048] = {0};
      if (Recv(client_fd, message_from_client, 2048, 0) == -1) {
        exit(EXIT_FAILURE);
      }

      printf("Message from client: %s\n", message_from_client);

      if (Send(client_fd, message_from_client, 2048, 0) == -1) {
        exit(EXIT_FAILURE);
      }

      close(client_fd);
      exit(0);
    }
    close(client_fd);
  }
}

void using_select(int server_fd) {
  printf("Using select() for synchronous multiplexing.\n");

  struct sockaddr_storage client_addr;
  socklen_t address_len = sizeof(struct sockaddr_storage);
  int client_fd;

  fd_set master;
  FD_ZERO(&master);
  FD_SET(server_fd, &master);
  int nfds = server_fd;

  while (1) {
    fd_set reads;
    reads = master;
    if (select(nfds + 1, &reads, NULL, NULL, /* timeout = */ NULL) < 0) {
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", errno);
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= nfds; ++i) {
      if (FD_ISSET(i, &reads)) {
        if (i == server_fd) {
          if ((client_fd = Accept(server_fd, (struct sockaddr *)&client_addr,
                                  (socklen_t *)&address_len)) == -1) {
            exit(EXIT_FAILURE);
          }
          FD_SET(client_fd, &master);
          if (client_fd > nfds)
            nfds = client_fd;
        } else {
          // read from a client socket
          if (read_and_echo(i)) {
            // client disconnected
            FD_CLR(i, &master);
            close(i);
          }
        }
      }
    }
  }
}