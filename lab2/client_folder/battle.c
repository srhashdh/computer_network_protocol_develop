#include "define.h"
void battle(cJSON *cjson){
    const char *cjson_rival = cJSON_GetObjectItem(cjson, "rival")->valuestring;
    const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;
    printf("battle start\n");
    while(1){
        char command[BUFFER_SIZE];
        printf("(a)scissor (b)stone (c))paper: ");
        
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = 0;
        if(strcmp(command, "a") == 0){
            cJSON *cjson = NULL;
            cjson = cJSON_CreateObject();
            cJSON_AddStringToObject(cjson, "name", cjson_name);
            cJSON_AddStringToObject(cjson, "rival", cjson_rival);
            cJSON_AddStringToObject(cjson, "request", "battle");
            cJSON_AddNumberToObject(cjson, "choice", 1);
            char *json_string = cJSON_PrintUnformatted(cjson);
            send(server_fd, json_string, strlen(json_string), 0);
            char *str = NULL;
            str = cJSON_Print(cjson);
            printf("json: %s\n", str);
            break;
        }
        else if(strcmp(command, "b") == 0){
            cJSON *cjson = NULL;
            cjson = cJSON_CreateObject();
            cJSON_AddStringToObject(cjson, "name", cjson_name);
            cJSON_AddStringToObject(cjson, "rival", cjson_rival);
            cJSON_AddStringToObject(cjson, "request", "battle");
            cJSON_AddNumberToObject(cjson, "choice", 2);
            char *json_string = cJSON_PrintUnformatted(cjson);
            send(server_fd, json_string, strlen(json_string), 0);
            char *str = NULL;
            str = cJSON_Print(cjson);
            printf("json: %s\n", str);
            break;
        }
        else if(strcmp(command, "c") == 0){
            cJSON *cjson = NULL;
            cjson = cJSON_CreateObject();
            cJSON_AddStringToObject(cjson, "name", cjson_name);
            cJSON_AddStringToObject(cjson, "rival", cjson_rival);
            cJSON_AddStringToObject(cjson, "request", "battle");
            cJSON_AddNumberToObject(cjson, "choice", 3);
            char *json_string = cJSON_PrintUnformatted(cjson);
            send(server_fd, json_string, strlen(json_string), 0);
            char *str = NULL;
            str = cJSON_Print(cjson);
            printf("json: %s\n", str);
            break;
        }
        else{
            printf("This battle command doesn't exit\n");
        }
    }
}