#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define MESSAGE_SIZE 34
#define response_SIZE 127

bool conn_01(int sockfd, const char *city) {
    char message[MESSAGE_SIZE]; 

    memset(message, '0', MESSAGE_SIZE - 1); 
    message[MESSAGE_SIZE - 1] = '\0';

    message[0] = 0x01;
    message[1] = 0x00;

    memcpy(message + 2, city, strlen(city));

    memset(message + 2 + strlen(city), 0x00, 34 - strlen(city));

    if (send(sockfd, message, MESSAGE_SIZE, 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    char response[response_SIZE];
    ssize_t num_bytes;
    if ((num_bytes = recv(sockfd, response, response_SIZE, 0)) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    if (response[0] == 0x01) {
        return true;
    }
    return false;
}
