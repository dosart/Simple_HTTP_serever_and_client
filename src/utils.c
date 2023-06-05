#include "utils.h"

static const char *method_names[] = {"simple", "fork", "select", "pool",
                                     "epoll"};

static int size = sizeof(method_names) / sizeof(method_names[0]);

static func_type method_funcs[] = {using_simple, using_fork, using_select};

static char *join(const char **strings, int num_strings);

static int get_index(const char *method, const char *method_names[], int size);

char *make_label(void) {
  return join(method_names, size);
}

static char *join(const char **strings, int num_strings) {
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

func_type find_method(const char *method_name) {
  int index = get_index(method_name, method_names, size);
  if (index == -1) {
    return NULL;
  }
  return method_funcs[index];
}

static int get_index(const char *method, const char *method_names[], int size) {
  for (int i = 0; i < size; i++) {
    if (strcmp(method_names[i], method) == 0)
      return i;
  }
  return -1;
}