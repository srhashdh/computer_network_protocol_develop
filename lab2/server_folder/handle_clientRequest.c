#include "define.h"

void *handle_clientRequest(void *arg) {
    struct client_info *client = (struct client_info *)arg;
    int client_fd = client->fd;

    while (1) {
        char message[BUFFER_SIZE];
        int valread = read(client_fd, message, BUFFER_SIZE);

        if (valread > 0) {
            message[valread] = '\0';  
            cJSON *cjson = cJSON_Parse(message);

            if (cjson == NULL) {
                printf("json parse fail\n");
                continue;
            }
            char *str = NULL;
            str = cJSON_Print(cjson);
            printf("json: %s\n", str);
            const char *request = cJSON_GetObjectItem(cjson, "request")->valuestring;
            const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;
            if (strcmp(request, "loggin") == 0) {
                //pthread_mutex_lock(&clients_mutex);
                loggin(client, cjson_name);
                //pthread_mutex_unlock(&clients_mutex);
            }
            else if(strcmp(request, "showList") == 0){
                //pthread_mutex_lock(&clients_mutex);
                send_showListToClient(client, cjson_name);
                //pthread_mutex_unlock(&clients_mutex);
            }
            else if(strcmp(request, "battleRequest") == 0){
                client -> state = STATE_IN_GAME;
                //pthread_mutex_lock(&clients_mutex);
                send_battleRequestToClient(client, cjson);
                //pthread_mutex_lock(&clients_mutex);
            }
            else if(strcmp(request, "battleRequestResult") == 0){
                //pthread_mutex_lock(&clients_mutex);
                send_battleRequestResultToClient(client, cjson);
                //pthread_mutex_lock(&clients_mutex);
            }
            else if(strcmp(request, "battle") == 0){
                client -> battle_res = true;
                int cjson_choice = cJSON_GetObjectItem(cjson, "choice")->valueint;
                client -> choice = cjson_choice;
                send_battleResult(client, cjson);
            }
        } else if (valread == 0) {
            
            char offline_client[BUFFER_SIZE];
            strcpy(offline_client, client -> name); 
            printf("player %s offline\n", client->name);
            close(client_fd);
            pthread_mutex_lock(&clients_mutex);
            for (int i = 0; i < MAX_EVENTS; i++) {
                if (clients[i] == client) {
                    clients[i] = NULL;
                    break;
                }
            }
            pthread_mutex_unlock(&clients_mutex);
            broadcast_toClients(offline_client, "offline");
            free(client);
            break;
        }
    }

    return NULL;
}
