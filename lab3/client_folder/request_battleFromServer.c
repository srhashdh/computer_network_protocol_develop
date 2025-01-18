#include "define.h"

void request_battleFromServer(int server_fd){
    char command[BUFFER_SIZE];
    printf("Enter a player who you want to battle?\n");
    fgets(command, BUFFER_SIZE, stdin);
    command[strcspn(command, "\n")] = 0;
    cJSON *cjson = NULL;
    char* str = NULL;
    cjson = cJSON_CreateObject();
    cJSON_AddStringToObject(cjson, "request", "battleRequest");
    cJSON_AddStringToObject(cjson, "name", info -> name);
    cJSON_AddStringToObject(cjson, "rival", command);
    char *json_string = cJSON_PrintUnformatted(cjson);
    send(server_fd, json_string, strlen(json_string), 0);
    cJSON_Delete(cjson);
    free(json_string);
}