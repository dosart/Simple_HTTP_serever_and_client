#ifndef CLIENT_V2_H
#define CLIENT_V2_H

#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int open_client_fd(char *hostname, char *port);

#endif