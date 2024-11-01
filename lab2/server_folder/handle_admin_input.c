#include "define.h"
void *handle_admin_input(void *arg){
    while(1){
        char command[BUFFER_SIZE];
        printf("Admin command (s)show client: \n");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = 0;
        
        if(strcmp(command, "s") == 0){
            pthread_mutex_lock(&clients_mutex);
            display_online_clients();
            pthread_mutex_unlock(&clients_mutex);
        }
        else{
            printf("this command doesn't exit");
        }
    }
    return NULL;
}
