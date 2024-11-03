#include "define.h"
void send_showListToClient(struct client_info *client, const char *cjson_name){
    printf("client %s request list\n", client -> name);


    cJSON *response = cJSON_CreateObject();
    cJSON *nameList = cJSON_CreateArray();
    cJSON *stateList = cJSON_CreateArray();

    
    cJSON_AddStringToObject(response, "type", "showList");

    for (int i = 0; i < MAX_EVENTS; i++) {
        if (clients[i] && clients[i]->state != STATE_NOT_LOGGED_IN && strcmp(clients[i]->name, cjson_name) != 0) {
            
            cJSON_AddItemToArray(nameList, cJSON_CreateString(clients[i]->name));
            if (clients[i]->state == STATE_IN_GAME) {
                cJSON_AddItemToArray(stateList, cJSON_CreateString("gaming"));
            }
            else if (clients[i]->state == STATE_IN_WAITING) {
                cJSON_AddItemToArray(stateList, cJSON_CreateString("waiting"));
            }
    
        }
    }

    
    cJSON_AddItemToObject(response, "nameList", nameList);
    cJSON_AddItemToObject(response, "stateList", stateList);
    
    char *json_string = cJSON_PrintUnformatted(response);
    
    send(client -> fd, json_string, strlen(json_string), 0);
    printf("send list to player %s, %d\n", client -> name, client -> fd);
    char *str = NULL;
    str = cJSON_Print(response);
    printf("json: %s\n", str);
    free(json_string);
    cJSON_Delete(response);

}