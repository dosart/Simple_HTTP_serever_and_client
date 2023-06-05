#include "methods.h"
#include "wrappers.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
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
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
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

    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
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

static void clear(char arr[], int size);

void using_select(int server_fd) {
  printf("Using select() for synchronous multiplexing.\n");

  struct sockaddr_storage client_addr;
  socklen_t address_len = sizeof(struct sockaddr_storage);
  char message_from_client[2048] = {0};
  int client_fd;

  fd_set read_set;
  FD_ZERO(&read_set);
  FD_SET(server_fd, &read_set);
  int maxfd = server_fd;

  while (1) {
    fd_set ready_set;
    ready_set = read_set;
    if (select(maxfd + 1, &ready_set, NULL, NULL, NULL) < 0) {
      fprintf(stderr, "select failed. (%d)\n", errno);
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= maxfd; ++i) {
      if (FD_ISSET(i, &ready_set)) {
        if (i == server_fd) {
          if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                                  (socklen_t *)&address_len)) == -1) {
            exit(EXIT_FAILURE);
          }
          FD_SET(client_fd, &read_set);
          if (client_fd > maxfd)
            maxfd = client_fd;
        } else {
          if (Recv(i, message_from_client, 2048, 0) == -1) {
            exit(EXIT_FAILURE);
          }

          printf("Message from client: %s\n", message_from_client);

          if (Send(i, message_from_client, 2048, 0) == -1) {
            exit(EXIT_FAILURE);
          }

          FD_CLR(i, &read_set);
          close(i);
          clear(message_from_client, 2048);
        }
      }
    }
    if (maxfd == FD_SETSIZE) {
      fprintf(stderr, "too many clients.\n");
      exit(EXIT_FAILURE);
    }
  }
}

static void clear(char arr[], int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = '\0';
  }
}