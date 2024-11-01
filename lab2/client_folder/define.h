#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdbool.h>
#include <netinet/in.h>
#include "cJSON.h"
#include <pthread.h>
#ifndef DEFINE_H
#define DEFINE_H
#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10

struct infomation{
    int fd;
    char name[BUFFER_SIZE];
    char rival[BUFFER_SIZE];
};
extern struct infomation *info;
int main();
void loggin_to_server(int server_fd);
void broadcast_fromServer(cJSON *cjson);
void request_listFromServer();
void *handle_clientCommand(void *arg);
void handle_serverResponse(int server_fd);
void show_listFromServer(cJSON *cjson);
#endif
