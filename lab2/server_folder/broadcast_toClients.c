#include "define.h"

void broadcast_toClients(char *player, char *state) {
    
    cJSON *cjson = cJSON_CreateObject();
    if (cjson == NULL) {
        printf("Failed to create JSON object\n");
        return;
    }

   
    cJSON_AddStringToObject(cjson, "player", player);
    cJSON_AddStringToObject(cjson, "state", state);
    cJSON_AddStringToObject(cjson, "type", "broadcast");
   
    char *json_string = cJSON_PrintUnformatted(cjson);
    if (json_string == NULL) {
        printf("Failed to print JSON string\n");
        cJSON_Delete(cjson);
        return;
    }

    
    for (int i = 0; i < MAX_EVENTS; i++) {
        if (clients[i] != NULL && clients[i]->state == STATE_IN_WAITING) {
            
            send(clients[i]->fd, json_string, strlen(json_string), 0);
        }
    }

    
    free(json_string);
    cJSON_Delete(cjson);
}
