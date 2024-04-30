#include <stdbool.h>
#include <stdint.h>
#ifndef define_H
#define define_H
int main();
void weather(const char *city, int sockfd);
int conn();
bool conn_01(int sockfd, const char *city);
void conn_02_01(int sockfd, const char *city, int n, int *t, int *w);
void conn_02_02(int sockfd, const char *city, int n, int *t_1, int *w_1, int *t_2, int *w_2, int *t_3, int *w_3);
typedef struct {
    uint8_t page;
    uint8_t query;
    char city[30];
    uint8_t date;
} request;
typedef struct {
    uint8_t page;
    uint8_t query;
    char city[30];
    char unknown1[4];
    uint8_t date;
    uint8_t weather_1;
    uint8_t temp_1;
    uint8_t weather_2;
    uint8_t temp_2;
    uint8_t weather_3;
    uint8_t temp_3;
    char unknown2[84];
} response;
#endif
