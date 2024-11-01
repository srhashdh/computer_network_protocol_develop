#include "define.h"
struct infomation *info = NULL;
pthread_mutex_t send_mutex = PTHREAD_MUTEX_INITIALIZER;
int main() {
    int server_fd;
    struct sockaddr_in server_addr;
    //char buffer[BUFFER_SIZE];
    //pthread_t server_response;

    //create admin thread to handle input
  //  pthread_create(&server_response, NULL, broadcast_fromServer, NULL);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Connected to server.\n");
    info = malloc(sizeof(struct infomation));
    info -> fd = server_fd;
    info -> name[0] = '\0';
    info -> rival[0] = '\0';
    //pthread_create(&server_response, NULL, broadcast_fromServer, &server_fd);
    loggin_to_server(server_fd);
/*
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
    */
    close(server_fd);

    return 0;
}

