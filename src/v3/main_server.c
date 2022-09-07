#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sigchld_handler(int sig) {
while (waitpid(-1, 0, WNOHANG) > 0)
  ;
return;
}

int main() {

  char *message_to_client = "HTTP/1.1 200 OK\nContent-Type: "
                            "text/plain\nContent-Length: 12\n\nHello world!";

  struct sockaddr_storage client_addr;
  socklen_t client_len = sizeof(struct sockaddr_storage);

  signal(SIGCHLD, sigchld_handler);
  int listen_fd, client_fd;
  listen_fd = Open_listen_fd("29008", 10);
  while (1) {
    printf("Server waiting\n\n");

    if ((client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                            (socklen_t *)&client_len)) < 0) {
      errno = client_fd;
      perror("accept");
    }

    if (fork() == 0) {
      close(listen_fd);

      char buffer[2048] = {0};
      recv(client_fd, buffer, 2048, 0);
      send(client_fd, message_to_client, strlen(message_to_client), 0);

      printf("Message from client: %s\n", buffer);

      close(client_fd);
      exit(0);
    }
    close(client_fd);
  }
  return 0;
}
