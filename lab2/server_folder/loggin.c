#include "define.h"

void loggin(struct client_info *client, const char* cjson_name){
    bool name_taken = false;
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_EVENTS; i++) {
        if (clients[i] && strcmp(clients[i]->name, cjson_name) == 0) {
            name_taken = true;
            break;
        }
    }

    cJSON *response = cJSON_CreateObject();
    if (!name_taken) {
        strcpy(client->name, cjson_name);
        broadcast_toClients(client->name, "online");
        client->state = STATE_IN_WAITING; 
        printf("Player %s logged in fd: %d\n", client->name, client -> fd);
        cJSON_AddStringToObject(response, "loggin", "success");
    } else {
        cJSON_AddStringToObject(response, "loggin", "fail");
    }
    cJSON_AddStringToObject(response, "name", client -> name);
    char *json_string = cJSON_PrintUnformatted(response);
    send(client->fd, json_string, strlen(json_string), 0);
    free(json_string);
    cJSON_Delete(response);
    pthread_mutex_unlock(&clients_mutex);
}