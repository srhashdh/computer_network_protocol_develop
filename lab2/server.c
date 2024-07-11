#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CLIENTS 5

int main(){
    int server_fd, new_socket, client_sockets[MAX_CLIENTS];
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    struct pollfd fds[MAX_CLIENTS + 1];
    int nfds = 1;
    int current_clients = 0;
    char buffer[1025];



    for(int i = 0; i < MAX_CLIENTS; i++){
        client_sockets[i] = 0;
    }

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }


    if(listen(server_fd, MAX_CLIENTS) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    fds[0].fd = server_fd;
    fds[0].events = POLLIN;

    printf("Server start. Waiting for connection on port %d...\n", PORT);

    while(1){
        int poll_status = poll(fds, nfds, -1);
        
        if(poll_status == -1){
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        if(fds[0].revents & POLLIN){
            if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0){
                perror("accept failed");
                exit(EXIT_FAILURE);
            }

            printf("New connection, IP is %s, port : %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            for(int i = 1; i < MAX_CLIENTS + 1; i++){
                if(client_sockets[i - 1] == 0){
                    client_sockets[i - 1] = new_socket;
                    fds[i].fd = new_socket;
                    fds[i].events = POLLIN;
                    nfds++;
                    current_clients++;
                    printf("Adding client to list of sockets as %d\n", i);
                    break;
                }
            }
        }
        for(int i = 1; i < nfds; i++){
            if(fds[i].revents & POLLIN){
                int client_socket = fds[i].fd;
                int valread;
            
                if((valread = read(client_socket, buffer, 1024)) == 0){
                
                    getpeername(client_socket, (struct sockaddr *)&address, (socklen_t *)&address);
                    printf("Host disconnected, IP %s, port %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(client_socket);
                    fds[i].fd = -1;
                    client_sockets[i - 1] = 0;
                    current_clients--;
                }
                else{
                    buffer[valread] = '\0';
                    printf("Client port %d messaage: %s\n", ntohs(address.sin_port), buffer);
                    send(client_socket, buffer, strlen(buffer), 0);
                }
            }
        }
    }
    return 0;
}
