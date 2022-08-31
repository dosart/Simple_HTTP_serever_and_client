#include "wrappers.h"

int open_client_fd(char *hostname, char *port) {
  
struct addrinfo hints, *results, *p;
  
memset(&hints, 0, sizeof(struct addrinfo));
hints.ai_socktype = SOCK_STREAM; // TCP socket
hints.ai_flags = AI_NUMERICSERV; // Port is number
hints.ai_flags |= AI_ADDRCONFIG;
Getaddrinfo(hostname, port, &hints, &results);

int client_fd;
// Find socket using hints. add socket to list of results
for (p = results; p; p = p->ai_next) {
if ((client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
continue; // Bad luck. Try next address

if (connect(client_fd, p->ai_addr, p->ai_addrlen) != -1)
break; // Good luck. Connect is successed.
close(client_fd;
}
Freeaddrinfo(results);
if (!p) // All address is wrong
return -1;
else 
return client_fd;
}

int main() { return 0; }
