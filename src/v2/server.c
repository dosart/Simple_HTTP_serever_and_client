#include "wrappers.h"

#define LISTENQ 10

int open_listen_fd(char *port) {
  struct addrinfo *settings, *setting;
  int optval = 1;
  
  struct addrinfo hints = {0}, *addrs;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
  hints.ai_flags |= AI_NUMERICSERV;
  
  Getaddrinfo(NULL, port, &hints, &addrs);

  int listen_fd, optval;
  for (struct addrinfo *addr = addrs; addr != NULL; addr = addr->ai_next)
  {
    listen_fd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (listen_fd == -1)
      continue;
    
    Setsockopt((listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
               
    if (bind(listen_fd, setting->ai_addr, setting->ai_addrlen) == 0)
               break; 
    else
               close(listen_fd);
  }
   
  Freeaddrinfo(addrs);
               
  if (addr == NULL)
    return -1;
  
 if (listen(listen_fd, LISTENQ) == -1) 
 {
   close(listen_fd);
   return -1; 
 }
 return server_fd; 
}
