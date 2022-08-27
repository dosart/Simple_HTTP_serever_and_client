#include "wrappers.h"

int connect_server(char *hostname, int port) {
  struct addrinfo hints, *settings, *setting;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE; // write my IP
  hints.ai_flags |= AI_NUMERICSERV; // port is number

  Getaddrinfo(hostname, port, &hints, &settings);
  int client_fd;
  for (setting = settings; setting; setting = setting->ai_next) {
    if ((client_fd = socket(setting->ai_family, setting->ai_socktype,
                            setting->ai_protocol) < 0))
      continue;
    if (connect(client_fd, setting->ai_addr, setting->ai_addrlen) == 0)
      break;
    close();
  }
  if (!setting)
    return -1;
  else
    return client_fd;
}

int main() {
  int client_fd = connect_server("127.0.0.1", "8080");

  char *message = "Hello from client";
  send(client_fd, message, strlen(message), 0);

  char buffer[2048] = {0};
  recv(client_fd, buffer, 2048, 0);

  printf("Message from server: %s\n", buffer);

  close(client_fd);
  return 0;
}
