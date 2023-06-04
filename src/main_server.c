#include "utils.h"
#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  char *label = make_label();

  if (argc < 3) {
    printf("Usage: server [port] [%s]\n", label);
    free(label);
    return 1;
  }

  const char *str_port = argv[1];
  unsigned long int_port = strtoul(str_port, NULL, 0);
  if (int_port < 1 || int_port > 65535) {
    printf("You must enter a valid port number.\n");
    return 1;
  }

  func_type method_func;
  const char *method = argv[2];
  if ((method_func = find_method(method)) == NULL) {
    printf("Unknown  method. Use  %s.\n", label);
    free(label);
    return 1;
  }

  int listen_fd = Open_listen_fd(str_port, 10);
  method_func(listen_fd);

  free(label);
}
