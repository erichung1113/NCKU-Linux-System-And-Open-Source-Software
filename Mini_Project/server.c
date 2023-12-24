#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX_LEN 1024
#define PORT 8080

int main(int argc, char const* argv[]) {
    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (true) {
        char input[MAX_LEN] = {0}, response[MAX_LEN] = {0}, command[MAX_LEN] = {0};
        valread = read(new_socket, input, MAX_LEN - 1);

        int num, num1, num2;
        if (strncmp(input, "add", 3) == 0) {
            sscanf(input, "%s %d %d", command, &num1, &num2);
            sprintf(response, "%d", num1 + num2);
        } else if (strncmp(input, "abs", 3) == 0) {
            sscanf(input, "%s %d", command, &num);
            sprintf(response, "%d", num > 0 ? num : -num);
        } else if (strncmp(input, "mul", 3) == 0) {
            sscanf(input, "%s %d %d", command, &num1, &num2);
            sprintf(response, "%d", num1 * num2);
        } else if (strcmp(input, "kill") == 0) {
            strcpy(response, "quit");
        } else {
            strcpy(response, "Hello");
        }
        send(new_socket, response, strlen(response), 0);
        if (strcmp(response, "quit") == 0) break;
    }
    close(new_socket);
    close(server_fd);
    return 0;
}
