#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "define.h"
#define request_SIZE 33
#define response_SIZE 127

bool conn_01(int sockfd, const char *city) {
    request req;
    req.page = 1; 
    req.query = 0;
    memcpy(req.city, city, strlen(city));
    memset(req.city + strlen(city), 0x00, 30 - strlen(city));
    req.date = 0;


    char buffer[sizeof(request)];
    memcpy(buffer, &req, sizeof(request));


    if (send(sockfd, buffer, sizeof(request), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    response res;
    ssize_t num_bytes;

    if ((num_bytes = recv(sockfd, &res, 1, 0)) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    if (res.page == 0x02) {
        return false;
    } else {
        return true;
    }
}
