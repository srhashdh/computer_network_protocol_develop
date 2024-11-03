#include "define.h"

void *handle_serverResponse(void *arg) {
    while (1) {
        char buffer[BUFFER_SIZE];
        
        int bytes_received = recv(server_fd, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received > 0) {
            
            buffer[bytes_received] = '\0';

           
            cJSON *cjson = cJSON_Parse(buffer);
            if (cjson == NULL) {
                printf("Parsed error: %s\n", cJSON_GetErrorPtr());
                continue; 
            }
            
            char *str = NULL;
            str = cJSON_Print(cjson);
            printf("json: %s\n", str);
            
            const char *cjson_type = cJSON_GetObjectItem(cjson, "type") -> valuestring;
            
            if(strcmp(cjson_type, "broadcast") == 0){
                printf("broadcast\n");
                broadcast_fromServer(cjson);
            }
            else if(strcmp(cjson_type, "showList") == 0){
                printf("show list\n");
                show_listFromServer(cjson);
            }
            else if(strcmp(cjson_type, "battleRequest") == 0){
                printf("battle request\n");
                //pthread_t battle_requestThread;
                battle_requestSignal = true;
                //pthread_create(&battle_requestThread, NULL, battle_request, (void *)cjson);
                battle_request(cjson);
                battle_requestSignal = false;
            }
            else if(strcmp(cjson_type, "battleStart") == 0){
                battlling_signal = true;
                battle(cjson);
                battlling_signal = false;
            }
            else if(strcmp(cjson_type, "battle") == 0){
                //battle_resultSignal = true;
                battle_result(cjson);
                //battle_resultSignal = false;
            }
            else{
                continue;
            }
            cJSON_Delete(cjson);
        }
        
        else {
            
            perror("recv failed");
            break;
        }
    }

    return NULL;
}
