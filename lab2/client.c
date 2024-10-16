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
    while(1){
        printf("What's your name: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        send(client_socket, buffer, strlen(buffer), 0);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if(bytes_received > 0){
            buffer[bytes_received] = '\0';
            printf("Server response: %s\n", buffer);
            
            if(strcmp(buffer, "Welcome, you have successfully logged in!") == 0){
                break;;
            }
        }
        else{
            printf("Server response: %s\n", buffer);
            continue;
        }
    }
    while (1){
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);

    return 0;
}

