#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "define.h"


void conn_02_01(int sockfd, const char *city, int n, int *t, int *w) {
    request req;
    req.page = 2;
    req.query = 1;
    memcpy(req.city, city, strlen(city));
    memset(req.city + strlen(city), 0x00, 30 - strlen(city));
    req.date = n;


    char buffer[sizeof(request)];
    memcpy(buffer, &req, sizeof(request));
    printf("buffer: %s\n", buffer);
    printf("req: %d\n", sockfd);
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
    *t = res.temp_1;
    *w = res.weather_1;
}
