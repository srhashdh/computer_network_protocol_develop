#include "define.h"

void display_online_clients(){
    printf("Online clients:\n");
    for(int i = 0; i < MAX_EVENTS; i++){
        if(clients[i]){
            printf("Clients %s\n", clients[i] -> name);
        }
    }
}
