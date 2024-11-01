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
            const char *cjson_name = cJSON_GetObjectItem(cjson, "name") -> valuestring;
            const char *cjson_loggin = cJSON_GetObjectItem(cjson, "loggin") -> valuestring;
            printf("%s loggin %s", cjson_name, cjson_loggin);
            
            if(strcmp(cjson_loggin, "success") == 0){
                printf(", welcome\n");
                strcpy(info -> name, cjson_name);
                
                /*
                pthread_t client_thread;
                pthread_create(&client_thread, NULL, handle_clientCommand, &server_fd);
                broadcast_fromServer(server_fd);
                */
                /*
                pthread_t broadcast;
                pthread_create(&broadcast, NULL, broadcast_fromServer, &server_fd);
                handle_clientCommand(server_fd);
                */
                pthread_t command;
                pthread_create(&command, NULL, handle_clientCommand, &server_fd);
                handle_serverResponse(server_fd);
            }
            else{
                printf("\n");
            }
            
        }
    }
    //pthread_t client_command;
    //broadcast;
    //client_command;
    //server response
    //broadcast_fromServer(server_fd);
    /*
    if(pthread_create(&broadcast, NULL, broadcast_fromServer, &server_fd) != 0){
        perror("Failed to create thread broadcast");
        return;
    }
    handle_clientCommand(server_fd);
    if (pthread_join(broadcast, NULL) != 0) {
        perror("Failed to join thread broadcast");
        return;
    }

    //client command
    if(pthread_create(&client_command, NULL, handle_clientCommand, &server_fd) != 0){
        perror("Failed to create thread client command");
        return;
    }
    if (pthread_join(client_command, NULL) != 0) {
        perror("Failed to join thread command");
        return;
    }
    */
}
