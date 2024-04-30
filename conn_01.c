#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "define.h"


bool conn_01(int sockfd, const char *city) {
    request req;
    req.page = 1; 
    req.query = 0;
    memcpy(req.city, city, strlen(city));
    memset(req.city + strlen(city), 0x00, 30 - strlen(city));
    req.date = 0;

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
	memcpy(&res, buffer2, sizeof(request));
    if (res.page == 2) {
        return false;
    } else {
        return true;
    }
}
