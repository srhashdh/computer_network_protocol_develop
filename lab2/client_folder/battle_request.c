#include "define.h"

void battle_request(cJSON *cjson){
    printf("battle\n");
    
    const char *cjson_rival = cJSON_GetObjectItem(cjson, "rival")->valuestring;
    const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;
    
    
    while(1){
        char command[BUFFER_SIZE];
        
        printf("%s want battle with you (y)yes (n)no ? ", cjson_rival);
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = 0;
        if(strcmp(command, "y") == 0){
            cJSON *cjson = NULL;
            cjson = cJSON_CreateObject();
            cJSON_AddStringToObject(cjson, "name", cjson_name);
            cJSON_AddStringToObject(cjson, "rival", cjson_rival);
            cJSON_AddStringToObject(cjson, "request", "battleRequestResult");
            cJSON_AddStringToObject(cjson, "result", "yes");
            char *json_string = cJSON_PrintUnformatted(cjson);
            send(server_fd, json_string, strlen(json_string), 0);
            char *str = NULL;
            str = cJSON_Print(cjson);
            printf("json: %s\n", str);
            break;
        }
        else if(strcmp(command, "n") == 0){
            cJSON *cjson = NULL;
            cjson = cJSON_CreateObject();
            cJSON_AddStringToObject(cjson, "name", cjson_name);
            cJSON_AddStringToObject(cjson, "rival", cjson_rival);
            cJSON_AddStringToObject(cjson, "request", "battleRequestResult");
            cJSON_AddStringToObject(cjson, "result", "no");
            char *json_string = cJSON_PrintUnformatted(cjson);
            send(server_fd, json_string, strlen(json_string), 0);
            break;
        }
        else{
            printf("This battle command doesn't exit\n");
        }
        
    }
}