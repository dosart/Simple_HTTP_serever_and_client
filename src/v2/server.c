#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LISTENQ 10
#define MAXLINE 2048

int open_listen_fd(char *port) {

  struct addrinfo hints, *listp, *p;

  int listenfd, optval = 1;

  /* Получить список потенциальных адресов сервера */

  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_socktype = SOCK_STREAM;
  /* Принимать соединения */

  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; /* ... на любом IP-адресе */

  hints.ai_flags |= AI_NUMERICSERV;
  /* ... номер порта -- число */

  Getaddrinfo(NULL, port, &hints, &listp);
  /* Найти адрес сокета, который можно связать */

  for (p = listp; p; p = p->ai_next) {

    /* Создать дескриптор сокета */

    if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)

      continue; /* Неудача, попробовать следующий адрес */

    /* Предотвратить появление ошибки "Адрес уже используется" */
    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,

               (const void *)&optval, sizeof(int));

    /* Связать дескриптор с адресом */

    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)

      break; /* Успех */

    close(listenfd); /* Ошибка, попробовать следующий адрес */
  }

  /* Освободить ресурсы */

  Freeaddrinfo(listp);

  if (!p) /* Ни один адрес не подошел */

    return -1;

  /* Сделать сокет слушающим и готовым принимать запросы на соединение */

  if (listen(listenfd, LISTENQ) < 0) {

    close(listenfd);

    return -1;
  }

  return listenfd;
}

int main() {
  int listenfd, connfd;

  socklen_t clientlen;

  struct sockaddr_storage clientaddr; /* Достаточно места для любого адреса */

  char client_hostname[MAXLINE], client_port[MAXLINE];
  char *message_to_client = "HTTP/1.1 200 OK\nContent-Type: "
                            "text/plain\nContent-Length: 12\n\nHello world!";

  listenfd = open_listen_fd("29008");

  while (1) {

    printf("Server waiting\n\n");
    clientlen = sizeof(struct sockaddr_storage);

    if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr,
                         (socklen_t *)&clientlen)) < 0) {
      perror("In accept");
      exit(EXIT_FAILURE);
    }

    // connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

    Getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname,
                MAXLINE,

                client_port, MAXLINE, 0);

    printf("Connected to (%s, %s)\n", client_hostname, client_port);

    char buffer[30000] = {0};
    read(connfd, buffer, 30000);
    printf("%s\n", buffer);
    write(connfd, message_to_client, strlen(message_to_client));
  }
  exit(0);
}
