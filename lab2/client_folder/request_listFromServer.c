#include "define.h"
void request_listFromServer(int server_fd){
    cJSON *cjson = NULL;
    char* str = NULL;
    cjson = cJSON_CreateObject();
    cJSON_AddStringToObject(cjson, "request", "showList");
    cJSON_AddStringToObject(cjson, "name", info -> name);
    char *json_string = cJSON_PrintUnformatted(cjson);
    send(server_fd, json_string, strlen(json_string), 0);
    cJSON_Delete(cjson);
    free(json_string);
    printf("client | state\n");
    /*
    //receive
    char buffer[BUFFER_SIZE];

    int bytes_received = recv(server_fd, buffer, BUFFER_SIZE, 0);
    if(bytes_received > 0){
        cJSON *cjson = cJSON_Parse(buffer);
        buffer[bytes_received] = '\0';
        if(cjson == NULL){
            printf("parsed error\n");
            return;
        }
        
        //char *json_string = cJSON_PrintUnformatted(cjson);
        //printf("%s\n", json_string);
        
        const char *cjson_type = cJSON_GetObjectItem(cjson, "type") -> valuestring;
        if(strcmp(cjson_type, "showList") == 0){
            cJSON *nameList = cJSON_GetObjectItem(cjson, "nameList");
            cJSON *stateList = cJSON_GetObjectItem(cjson, "stateList");
            int len = cJSON_GetArraySize(nameList);
            if(cJSON_IsArray(nameList) && cJSON_IsArray(stateList)){
                int name_listLen = cJSON_GetArraySize(nameList);
                int state_listLen = cJSON_GetArraySize(stateList);
                if(name_listLen == state_listLen){
                    for(int i = 0; i < name_listLen; i++){
                        cJSON* name = cJSON_GetArrayItem(nameList, i);
                        cJSON* state = cJSON_GetArrayItem(stateList, i);
                        const char *name_str = cJSON_GetStringValue(name);
                        const char *state_str = cJSON_GetStringValue(state);
                        printf("player %s  is %s\n", name_str, state_str);
                    }
                }
            }
        }
        printf("show list success\n");
    }
    */
}