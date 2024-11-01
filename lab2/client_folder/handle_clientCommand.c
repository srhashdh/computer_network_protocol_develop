#include "define.h"

void *handle_clientCommand(void *arg) {
    int server_fd = *(int *)arg;
    while(1){
        char command[BUFFER_SIZE];
        printf("client command (s)show client (b)battle: \n");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = 0;
        
        if(strcmp(command, "s") == 0){
            request_listFromServer(server_fd);
        }
        
        else{
            printf("this command doesn't exit");
        }
    }
    return NULL;
}
