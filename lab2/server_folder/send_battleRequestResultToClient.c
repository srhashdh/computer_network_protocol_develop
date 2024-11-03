#include "define.h"

void send_battleRequestResultToClient(struct client_info *client, cJSON *cjson){
    const char *cjson_rival = cJSON_GetObjectItem(cjson, "rival") -> valuestring;
    const char *cjson_name = cJSON_GetObjectItem(cjson, "name") -> valuestring;
    printf("client %s battle response.\n", client -> name);
    
    int rival_fd;
    const char *cjson_result = cJSON_GetObjectItem(cjson, "result") -> valuestring;
    int i = 0;
    
    for (i = 0; i < MAX_EVENTS; i++) {
        if (clients[i] && strcmp(clients[i]->name, cjson_rival) == 0) {
            rival_fd = clients[i] -> fd;
            break;
        }
    }
    
    if(strcmp(cjson_result, "yes") == 0){
        cJSON *response_player1 = cJSON_CreateObject();
        cJSON_AddStringToObject(response_player1, "name", cjson_name);
        cJSON_AddStringToObject(response_player1, "rival", cjson_rival);
        cJSON_AddStringToObject(response_player1, "type", "battleStart");
        char *json_string1 = cJSON_PrintUnformatted(response_player1);
        send(client -> fd, json_string1, strlen(json_string1), 0);


        cJSON *response_player2 = cJSON_CreateObject();
        cJSON_AddStringToObject(response_player2, "name", cjson_rival);
        cJSON_AddStringToObject(response_player2, "rival", cjson_name);
        cJSON_AddStringToObject(response_player2, "type", "battleStart");
        char *json_string2 = cJSON_PrintUnformatted(response_player2);
        send(rival_fd, json_string2, strlen(json_string2), 0);

        char *str = NULL;
        str = cJSON_Print(response_player1);
        printf("json: %s\n", str);

        free(json_string1);
        cJSON_Delete(response_player1);
        free(json_string2);
        cJSON_Delete(response_player2);
    }
    else if(strcmp(cjson_result, "no") == 0){
        cJSON *response_player1 = cJSON_CreateObject();
        cJSON_AddStringToObject(response_player1, "name", cjson_name);
        cJSON_AddStringToObject(response_player1, "rival", cjson_rival);
        cJSON_AddStringToObject(response_player1, "type", "battleEnd");
        char *json_string1 = cJSON_PrintUnformatted(response_player1);
        send(client -> fd, json_string1, strlen(json_string1), 0);


        cJSON *response_player2 = cJSON_CreateObject();
        cJSON_AddStringToObject(response_player2, "name", cjson_rival);
        cJSON_AddStringToObject(response_player2, "rival", cjson_name);
        cJSON_AddStringToObject(response_player2, "type", "battleEnd");
        char *json_string2 = cJSON_PrintUnformatted(response_player2);
        send(rival_fd, json_string2, strlen(json_string2), 0);

        char *str = NULL;
        str = cJSON_Print(response_player2);
        printf("json: %s\n", str);


        free(json_string1);
        cJSON_Delete(response_player1);
        free(json_string2);
        cJSON_Delete(response_player2);
        client -> state = STATE_IN_WAITING;
        clients[i] -> state = STATE_IN_WAITING;
    }
}