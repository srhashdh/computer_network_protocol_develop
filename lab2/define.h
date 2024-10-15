
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#ifndef DEFINE_H
#define DEFINE_H
#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10
struct client_info{
    int fd;
    struct sockaddr_in addr;
    char name[BUFFER_SIZE];
};


struct client_info *clients[MAX_EVENTS] = { NULL };
//non-block I/O
void set_nonblocking(int sock){
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}
#endif
