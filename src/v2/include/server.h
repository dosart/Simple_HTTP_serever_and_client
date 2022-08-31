#ifndef SERVER_V2_H
#define SERVER_V2_H

#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LISTENQ 10
#define CLIENT_HOSTNAME_SIZE 2048
#define CLIENT_PORT_SIZE 64
#define MESSAGE_FROM_CLIENT_LEN 4096

int open_listen_fd(char *port);

void set_empty(char *str, size_t str_size);

#endif