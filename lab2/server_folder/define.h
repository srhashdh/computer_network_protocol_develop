#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <pthread.h>
#include "cJSON.h"
#ifndef DEFINE_H
#define DEFINE_H
#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10
enum client_state {
    STATE_NOT_LOGGED_IN,
    STATE_IN_GAME,
    STATE_IN_WAITING
};

struct client_info{
    int fd;
    struct sockaddr_in addr;
    char name[BUFFER_SIZE];
    enum client_state state;
};
extern struct client_info *clients[MAX_EVENTS];;
void loggin_clients(int epoll_fd, int server_fd);
int main();
void display_online_clients();
void *handle_admin_input(void *args);
void broadcast_toClients(char *player, char *state);
#endif
