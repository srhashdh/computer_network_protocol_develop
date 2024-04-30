#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "define.h"


void conn_02_01(int sockfd, const char *city, int n, int *t, int *w) {
    request req;
    req.page = 0x02;
    req.query = 0x01;
    memcpy(req.city, city, strlen(city));
    memset(req.city + strlen(city), 0x00, 30 - strlen(city));
    req.date = n;


    char buffer1[sizeof(request)];
    memcpy(buffer1, &req, sizeof(request));
    if (send(sockfd, buffer1, sizeof(request), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    response res;
    ssize_t num_bytes;
	char buffer2[sizeof(response)];
    if ((num_bytes = recv(sockfd, buffer2, sizeof(response), 0)) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    memcpy(&res, buffer2, sizeof(response));
    
	*t = res.temp_1;
    *w = res.weather_1;
}
