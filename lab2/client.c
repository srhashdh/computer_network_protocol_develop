#include "define.h"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);

    return 0;
}

