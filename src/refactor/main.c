
#include "methods.h"
#include "wrappers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  if (argc < 3) {
    printf("Usage: echo_server [port] [simple|fork|select|poll|epoll]\n");
    return 1;
  }

  const char *str_port = argv[1];
  unsigned long int_port = strtoul(str_port, NULL, 0);
  if (int_port < 1 || int_port > 65535) {
    printf("You must enter a valid str_port number.\n");
    return 1;
  }

  const char *method = argv[2];
  if (strcmp(method, "simple") && strcmp(method, "select") &&
      strcmp(method, "poll") && strcmp(method, "epoll")) {
    printf("Unknown multiplexing method. Use simple, select, poll or epoll.\n");
    return 1;
  }

  int listen_fd = Open_listen_fd(str_port, 10);

  if (strcmp(method, "simple") == 0) {
    using_simple(listen_fd);
  }

  if (strcmp(method, "fork") == 0) {
    using_fork(listen_fd);
  }
}
