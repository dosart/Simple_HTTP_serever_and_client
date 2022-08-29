#include "wrappers.h"

int open_connect(char *port) {
  struct addrinfo *settings, *setting;
  int optval = 1;
  
  struct addrinfo hints = {0}, *addrs;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
  hints.ai_flags |= AI_NUMERICSERV;
  
  Getaddrinfo(NULL, port, &hints, &addrs);

  int server_fd;
  for (setting = settings; setting; setting = setting->ai_next) {
    if ((server_fd = socket(setting->ai_family, setting->ai_socktype,
                           setting->ai_protocol) < 0))
      continue;
  
    Setsockopt((server_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
    
    if (bind(server_fd, setting->ai_addr, setting->ai_addrlen) == 0)
               break; 
    else
       close(server_fd); 
  }
               
  Freeaddrinfo(settings);
               
  if (!setting)
    return -1;
  
 if (listen(server_fd, LISTENQ) < 0) {
   close(listenfd);
   return -1; }
return server_fd;
  
}
