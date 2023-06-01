
#include "methods.h"
#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>

static char *make_label(const char **strings, int num_strings);

static const char *method_names[] = {"simple", "fork", "select", "pool",
                                     "epoll"};
static int size = sizeof(method_names) / sizeof(method_names[0]);

static int find_method(const char *method, const char *method_names[],
                       int size);

typedef void (*func_type)(int);
func_type method_funcs[] = {using_simple, using_fork};

int main(int argc, char const *argv[]) {
  char *label = make_label(method_names, size);

  if (argc < 3) {
    printf("Usage: server [port] [%s]\n", label);
    return 1;
  }

  const char *str_port = argv[1];
  unsigned long int_port = strtoul(str_port, NULL, 0);
  if (int_port < 1 || int_port > 65535) {
    printf("You must enter a valid port number.\n");
    return 1;
  }

  const char *method = argv[2];
  int method_index = 0;
  if ((method_index = find_method(method, method_names, size)) == -1) {
    printf("Unknown  method. Use  %s.\n", label);
    return 1;
  }

  int listen_fd = Open_listen_fd(str_port, 10);

  func_type method_func = method_funcs[method_index];
  method_func(listen_fd);

  free(label);
}

static char *make_label(const char **strings, int num_strings) {
  int i = 0;
  unsigned long total_length = 0;
  char *result;

  // Calculate total length of all strings
  for (i = 0; i < num_strings; i++) {
    total_length += strlen(strings[i]);
  }

  // Allocate memory for result string
  result = (char *)malloc((total_length + 1) * sizeof(char));

  // Concatenate strings
  strcpy(result, strings[0]);
  for (i = 1; i < num_strings; i++) {
    strcat(result, "|");
    strcat(result, strings[i]);
  }

  return result;
}

static int find_method(const char *method, const char *methods[], int size) {
  for (int i = 0; i < size; i++) {
    if (strcmp(methods[i], method) == 0)
      return i;
  }
  return -1;
}