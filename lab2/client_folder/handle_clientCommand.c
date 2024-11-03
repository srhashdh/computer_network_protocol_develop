#include "define.h"

void handle_clientCommand(int server_fd) {
    bool mainPrint = 0;
    while (1) {
        char command[BUFFER_SIZE];
        if(!mainPrint){
            printf("client command (s)show client (b)battle: \n");
        }
        struct timeval timeout;
        timeout.tv_sec = 0.5; // 超时时间为1秒
        timeout.tv_usec = 0;

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        command[strcspn(command, "\n")] = 0;     
        int activity = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

        if (activity > 0) {
            // 有输入
            if (FD_ISSET(STDIN_FILENO, &read_fds)) {
                fgets(command, BUFFER_SIZE, stdin);
                command[strcspn(command, "\n")] = 0;
                mainPrint = 0;

                if (strcmp(command, "s") == 0) {
                    request_listFromServer(server_fd);
                } else if (strcmp(command, "b") == 0) {
                    //pthread_mutex_lock(&command_mutex);
                    request_battleFromServer(server_fd);
                    //pthread_mutex_unlock(&command_mutex);
                } else {
                    printf("This client command doesn't exist\n");
                }
            }
        } else {
            // 超时，没有输入
            
            mainPrint = 1;
            while(battle_requestSignal || battlling_signal){
                    
            }
            
        }
    }   
   /*
    while(1){
        char command[BUFFER_SIZE];
        printf("client command (s)show client (b)battle: \n");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = 0;
        
        if(strcmp(command, "s") == 0){
            request_listFromServer(server_fd);
        }
        else if(strcmp(command, "b") == 0){
            pthread_mutex_lock(&command_mutex);
            request_battleFromServer(server_fd);
            pthread_mutex_unlock(&command_mutex);
        }
        else{
            printf("This client command doesn't exit\n");
        }
        
    }
    */
    return;
}
