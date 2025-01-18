#include "define.h"

struct client_info *clients[MAX_EVENTS] = { NULL };
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void cleanup(int epoll_fd, int server_fd, pthread_t admin_thread) {
    close(epoll_fd);
    close(server_fd);
    pthread_cancel(admin_thread);
    pthread_join(admin_thread, NULL);
}

int main() {
    int server_fd, epoll_fd;
    struct sockaddr_in address;
    int opt = 1;
    struct epoll_event event;

    pthread_t admin_thread;

    
    if (pthread_create(&admin_thread, NULL, handle_admin_input, NULL) != 0) {
        perror("Failed to create admin thread");
        return EXIT_FAILURE;
    }

    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return EXIT_FAILURE;
    }

    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen failed");
        return EXIT_FAILURE;
    }

    
    if ((epoll_fd = epoll_create1(0)) < 0) {
        perror("Epoll creation failed");
        return EXIT_FAILURE;
    }

    event.events = EPOLLIN;
    event.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) < 0) {
        perror("Epoll_ctl failed");
        return EXIT_FAILURE;
    }

    connect_toClients(epoll_fd, server_fd);

    cleanup(epoll_fd, server_fd, admin_thread);
    return 0;
}
