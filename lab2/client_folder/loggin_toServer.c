#include "define.h"
void loggin_to_server(int server_fd){




    //char buffer[BUFFER_SIZE];
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
            const char *cjson_loggin = cJSON_GetObjectItem(cjson, "loggin") -> valuestring;
            printf("loggin %s", cjson_loggin);
            
            if(strcmp(cjson_loggin, "success") == 0){
                printf(", welcome\n");
                break;
            }
            else{
                printf("\n");
            }
            
        }
        else{
            printf("Server response: %s\n", buffer);
            continue;
        }
    }
    while (1){
        char buffer[BUFFER_SIZE];
        pthread_t server_response;
        pthread_create(&server_response, NULL, broadcast_fromServer, &server_fd);
    }


}
