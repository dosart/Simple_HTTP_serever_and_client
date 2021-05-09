// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int server_fd = 0;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket create error");
        exit(EXIT_FAILURE);
    }


    const uint16_t port = 8080;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    memset(address.sin_zero, 0, sizeof(address.sin_zero));

    if (bind(server_fd, (struct sockaddr*)&address, sizeof (address)) == -1) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    const uint32_t backlog = 10;
    if (listen(server_fd, backlog) == -1) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }


    struct sockaddr client_address;
    while (1) {
        printf("----------Server waiting----------\n\n");

        int client_fd = 0;
        if ((client_fd = accept(server_fd, &client_address, sizeof(client_address))) == -1) {
            perror("accept error");
            exit(EXIT_FAILURE);
        }

        char buffer[2048] = {0};
        while (1) {
            if (recv(client_fd, buffer, sizeof(buffer), 0) == -1)
                break;
        }
        printf("Client %s\n",client_address.sa_data);
        printf("Message %s\n", buffer);

        close(client_fd);
    }
    return 0;
}
