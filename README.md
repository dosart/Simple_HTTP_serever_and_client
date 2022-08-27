# Simple HTTP server and client for demonstrate Socket programming

## Old style. Manual struct sockaddr_in filling

- [Server](https://github.com/dosart/Simple_HTTP_server_and_client/blob/main/src/v1/http_server.c)
- [Client](https://github.com/dosart/Simple_HTTP_server_and_client/blob/main/src/v1/http_client.c)

## Modern style. Using function getaddrinfo + system call wrappers.

- [Server](https://github.com/dosart/Simple_HTTP_server_and_client/blob/main/src/v2/server.c)
- [Client](https://github.com/dosart/Simple_HTTP_server_and_client/blob/main/src/v2/client.c)
