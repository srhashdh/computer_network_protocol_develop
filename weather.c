#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "define.h"
#include <stdbool.h>
void weather(const char *city){
    while(1){
        char number[20];
        printf("Please enter the given number to query\n");
        printf("1.today\n");
        printf("2.three days from today\n");
        printf("3.custom day by yourself\n");
        printf("(r)back,(c)cls,(#)exit\n");
        printf("==========================================================\n");
        scanf("%s", number);
        bool flag = false;
        while(!flag){
            time_t t = time(NULL);
            struct tm *now = localtime(&t);
            if(strcmp(number, "1") == 0){
                printf("City: %s  Today is: %d/%02d/%02d Weather information is as follow:\n", city, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
                printf("Today's Weather is: \n");
            }
            else if(strcmp(number, "2") == 0){
                printf("City: %s  Today is: %d/%02d/%02d Weather information is as follow:\n", city, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
                printf("The 1th day's Weather is: \n");
                printf("The 2th day's Weather is: \n");
                printf("The 3th day's Weather is: \n");
            }
            else if(strcmp(number, "3") == 0){
                printf("Please enter the day number(below 10, e.g. 1 means today):");
                bool flag2 = false;
                while(!flag2){
                    int n;
                    printf("Please enter the day number(below 10, e.g. 1 means today):");
                    scanf("%d", &n);
                    if(n > 1 && n < 10){
                        printf("City: %s  Today is: %d/%02d/%02d Weather information is as follow:\n", city, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
                        printf("The %dth day's Weather is: \n", n);
                        flag2 = true;
                    }
                    else if(n == 1){
                        printf("City: %s  Today is: %d/%02d/%02d Weather information is as follow:\n", city, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
                        printf("Today's Weather is: \n");
                        flag2 = true;
                    }
                    else{
                        printf("input error!\n");
                    }
                }
            }
            else if(strcmp(number, "r") == 0){
                main();
            }
            else if(strcmp(number, "c") == 0){
                system("clear");
                break;
            }
            else if(strcmp(number, "#") == 0){
                exit(0);
            }
            else{
                printf("input error!\n");
            }
            scanf("%s", number);
        }
    }
}