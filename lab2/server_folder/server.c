#include "define.h"
struct client_info *clients[MAX_EVENTS] = { NULL };
int main(){
    int server_fd, epoll_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    struct epoll_event event, events[MAX_EVENTS];
    
    pthread_t admin_thread;

    //create admin thread to handle input
    pthread_create(&admin_thread, NULL, handle_admin_input, NULL);
    
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
    
    loggin_clients(epoll_fd, server_fd);

    close(server_fd);
    return 0;
}
