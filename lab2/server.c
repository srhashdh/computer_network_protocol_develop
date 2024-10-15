#include "define.h"

int main(){
    int server_fd, epoll_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    struct epoll_event event, events[MAX_EVENTS];

    //create server socket

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, SOMAXCONN);

    //create epoll instance

    epoll_fd = epoll_create1(0);
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);
    
    while(1){
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for(int i = 0; i < n; i++){
            if(events[i].data.fd == server_fd){
                //accept new connection
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
                
                //set to non-blocking model
                set_nonblocking(client_fd);                    
                //distribute memory and store client info
                struct client_info *client = malloc(sizeof(struct client_info));
                client -> fd = client_fd;
                client -> addr = client_addr;
                client -> name[0] = '\0';
                for(int j = 0; j < MAX_EVENTS; j++){
                    if(!clients[j]){
                        clients[j] = client;
                        break;
                    }
                }
                    
                event.events = EPOLLIN;
                event.data.ptr = client;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
                printf("New connection from %s: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            }
                
            else{
                //handle client info
                struct client_info *client = (struct client_info *)events[i].data.ptr;
                char buffer[BUFFER_SIZE];
                int valread = read(client -> fd, buffer, BUFFER_SIZE);
                
                if(valread > 0){
                    buffer[valread] = '\0'; //make sure the string is null terminated
                    if(client -> name[0] == '\0'){
                        strcpy(client -> name, buffer);
                        printf("Player %s logged in\n", client -> name);
                        continue;
                    }
                    /*
                    char client_ip[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &(client -> addr.sin_addr), client_ip, INET_ADDRSTRLEN);
                    */
                    printf("Message from Player %s: %s\n", client -> name, buffer);
                }
                else{
                    printf("Player %s disconnected\n", client -> name);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client -> fd, NULL);

                    close(client -> fd);
                    //free memory
                    for(int j = 0; j < MAX_EVENTS; j++){
                        if(clients[j] == client){
                            free(client);
                            clients[j]= NULL;
                            break;
                        }
                    }
                }              
            }
        }
    }

    close(server_fd);
    return 0;
}
