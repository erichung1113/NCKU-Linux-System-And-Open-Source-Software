#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX_LEN 1024
#define PORT 8080

int main(int argc, char const* argv[]) {
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    while (true) {
        char input[MAX_LEN] = {0}, response[MAX_LEN] = {0};
        scanf("%[^\n]", input); getchar();
        
        send(client_fd, input, strlen(input), 0);
        read(client_fd, response, MAX_LEN - 1);

        if (strcmp(response, "quit") == 0) break;
        printf("%s\n", response);
    }
    close(client_fd);
    return 0;
}
