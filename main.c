#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "define.h"
int main(){
    system("clear");
    int sockfd = conn();
    while(1){
        char city[20];
        printf("Welcome to NJUCS Weather Forecast Demo Program!\n");
        printf("Please input City Name in Chinese pinyin(e.g. nanjin or beijin)\n");
        printf("(c)cls,(#)exit\n");
        scanf("%s", city);
        if(strcmp(city, "c") == 0){
            system("clear");
            continue;
        }
        else if(strcmp(city, "#") == 0){
            exit(0);
        }
        bool flag = conn_01(sockfd, city);
        if(!flag){
            printf("Sorry, Server does not have weather information for city %s\n", city);
        }
        else{
            system("clear");
            weather(city, sockfd);
        }   
    }
    return 0;
}