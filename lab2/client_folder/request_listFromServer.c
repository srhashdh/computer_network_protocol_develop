#include "define.h"
void request_listFromServer(int server_fd){
    cJSON *cjson = NULL;
    cjson = cJSON_CreateObject();
    cJSON_AddStringToObject(cjson, "request", "showList");
    cJSON_AddStringToObject(cjson, "name", info -> name);
    char *json_string = cJSON_PrintUnformatted(cjson);
    send(server_fd, json_string, strlen(json_string), 0);
    char *str = NULL;
    str = cJSON_Print(cjson);
    printf("json: %s\n", str);
    cJSON_Delete(cjson);
    free(json_string);
    printf("client and state\n");
}