#include "define.h"
void loggin_to_server(int server_fd){




    
    while(1){
        char buffer[BUFFER_SIZE];
        printf("What's your name: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        cJSON *cjson = NULL;
        cjson = cJSON_CreateObject();
        cJSON_AddStringToObject(cjson, "request", "loggin");
        cJSON_AddStringToObject(cjson, "name", buffer);
        char *json_string = cJSON_PrintUnformatted(cjson);
        send(server_fd, json_string, strlen(json_string), 0);

        cJSON_Delete(cjson);
        free(json_string);

        int bytes_received = recv(server_fd, buffer, BUFFER_SIZE, 0);
        if(bytes_received > 0){
            cJSON *cjson = cJSON_Parse(buffer);
            buffer[bytes_received] = '\0';
            if(cjson == NULL){
                printf("parsed error\n");
                return;
            }
            char *str = NULL;
            str = cJSON_Print(cjson);
            printf("json: %s\n", str);
            const char *cjson_name = cJSON_GetObjectItem(cjson, "name") -> valuestring;
            const char *cjson_loggin = cJSON_GetObjectItem(cjson, "loggin") -> valuestring;
            printf("%s loggin %s", cjson_name, cjson_loggin);
            
            if(strcmp(cjson_loggin, "success") == 0){
                printf(", welcome\n");
                strcpy(info -> name, cjson_name);
                
                /*
                pthread_t command;
                pthread_create(&command, NULL, handle_clientCommand, &server_fd);
                handle_serverResponse(server_fd);
                */
                pthread_t response;
                pthread_create(&response, NULL, handle_serverResponse, NULL);
                handle_clientCommand(server_fd);
            }
            else{
                printf("\n");
            }
            
        }
    }
    
}
