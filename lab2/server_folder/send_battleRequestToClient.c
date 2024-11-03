#include "define.h"

void send_battleRequestToClient(struct client_info *client, cJSON *cjson){
    const char *cjson_rival = cJSON_GetObjectItem(cjson, "rival")->valuestring;
    const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;
    printf("client %s request battle to %s\n", client -> name, cjson_rival);
    int rival_fd;
    bool flag = false;
    for (int i = 0; i < MAX_EVENTS; i++) {
        if (clients[i] && clients[i]->state == STATE_IN_WAITING && strcmp(clients[i]->name, cjson_rival) == 0 && strcmp(clients[i]->name, cjson_name) != 0) {
            rival_fd = clients[i] -> fd;
            clients[i] -> state = STATE_IN_GAME;
            flag = true;
            break;
        }
    }
    cJSON *response = cJSON_CreateObject();
    cJSON_AddStringToObject(response, "name", cjson_rival);
    cJSON_AddStringToObject(response, "rival", cjson_name);
    if(flag){
        cJSON_AddStringToObject(response, "type", "battleRequest");
        char *json_string = cJSON_PrintUnformatted(response);
        send(rival_fd, json_string, strlen(json_string), 0);
        printf("find %s fd: %d\n", cjson_rival, rival_fd);
        char *str = NULL;
        str = cJSON_Print(response);
        printf("json: %s\n", str);
        free(json_string);
        cJSON_Delete(response);
    }
    else{
        cJSON_AddStringToObject(response, "type", "battleResponse");
        cJSON_AddStringToObject(response, "result", "fail");
        char *json_string = cJSON_PrintUnformatted(response);
        send(client -> fd, json_string, strlen(json_string), 0);
        printf("doesn't find %s\n", cjson_rival);
        char *str = NULL;
        str = cJSON_Print(response);
        printf("json: %s\n", str);
        free(json_string);
        cJSON_Delete(response);
    }
    /*
    if(flag){
        cJSON_AddStringToObject(response, "result", "success");
        printf("player %s and %s battle request success\n", client -> name, cjson_rival);
    }
    else{
        cJSON_AddStringToObject(response, "result", "fail");
        printf("player %s and %s battle request fail\n", client -> name, cjson_rival);
    }
    char *json_string = cJSON_PrintUnformatted(response);
    send(client -> fd, json_string, strlen(json_string), 0);
    printf("player %s a %s\n", client -> name, client -> fd);
    
    free(json_string);
    cJSON_Delete(response);
    */
}