#ifndef UTILS_H
#define UTILS_H

#include "methods.h"
#include <stdlib.h>
#include <string.h>

char *make_label();

typedef void (*func_type)(int);

func_type find_method(const char *method_name);

#endif