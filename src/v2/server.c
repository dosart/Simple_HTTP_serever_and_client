#include "wrappers.h"

int connect_server(char *hostname, int port) {
  struct addrinfo hints, *settings, *setting;

  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV;
  hints.ai_flags = AI_ADDRCONFIG;

  Getaddrinfo(hostname, port, &hints, &settings);
  int serverfd;
  for (setting = settings; setting; setting = setting->ai_next) {
    if ((serverfd = socket(setting->ai_family, setting->ai_socktype,
                           setting->ai_protocol) < 0))
      continue;
    if (connect(serverfd, setting->ai_addr, setting->ai_addrlen) == 0)
      break;
    close();
  }
  Freeaddrinfo(settings);
  if (!setting)
    return -1;
  else
    return serverfd;
}