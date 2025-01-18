#include "define.h"

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
void connect_toClients(int epoll_fd, int server_fd) {
    struct epoll_event events[MAX_EVENTS];

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == server_fd) {
                
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
                set_nonblocking(client_fd);
                
                struct client_info *client = malloc(sizeof(struct client_info));
                client->fd = client_fd;
                client->addr = client_addr;
                client->name[0] = '\0';
                client->state = STATE_NOT_LOGGED_IN; 
                client->battle_res = false;
                client->choice = 0;
                for (int j = 0; j < MAX_EVENTS; j++) {
                    if (!clients[j]) {
                        clients[j] = client;
                        break;
                    }
                }
                struct epoll_event event;
                event.events = EPOLLIN;
                event.data.ptr = client;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
                
                pthread_t client_thread;
                pthread_create(&client_thread, NULL, handle_clientRequest, (void *)client);
                pthread_detach(client_thread);
            }
            
        }
    }
}
