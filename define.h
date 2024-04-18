#include <stdbool.h>
#ifndef define_H
#define define_H
int main();
void weather(const char *city, int sockfd);
int conn();
bool conn_01(int sockfd, const char *city);
void conn_02_01(int sockfd, const char *city, int n);
#endif