#include "define.h"

void *handle_clientRequest(void *arg) {
    struct client_info *client = (struct client_info *)arg;
    int client_fd = client->fd;

    while (1) {
        char message[BUFFER_SIZE];
        int valread = read(client_fd, message, BUFFER_SIZE);

        if (valread > 0) {
            message[valread] = '\0';  // 确保字符串以 null 结尾
            cJSON *cjson = cJSON_Parse(message);

            if (cjson == NULL) {
                printf("json parse fail\n");
                continue;
            }

            const char *request = cJSON_GetObjectItem(cjson, "request")->valuestring;
            const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;
            if (strcmp(request, "loggin") == 0) {
                loggin(client, cjson_name);
                /*
                const char *name = cJSON_GetObjectItem(cjson, "name")->valuestring;
                
                pthread_mutex_lock(&clients_mutex);
                bool name_taken = false;

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
                */
            }
            else if(strcmp(request, "showList") == 0){
                send_showListToClient(client, cjson_name);
                // 处理其他已登录的请求，例如 showList
                // ...
            }

            
        } else if (valread == 0) {
            // 断开连接处理
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
/*
void *handle_clientRequest(void *arg){
    struct client_info *client = (struct client_info *)arg;
    int client_fd = client->fd;
    while(1){
        char message[BUFFER_SIZE];
        //printf("player %s request\n", client -> name);
        
        int valread = read(client_fd, message, BUFFER_SIZE);
        
        if (valread > 0) {
            
            message[valread] = '\0';
            cJSON *cjson = cJSON_Parse(message);
            if (cjson == NULL) {
              printf("Parsed error\n");
              return NULL;
            }
            
            const char *cjson_req = cJSON_GetObjectItem(cjson, "request")->valuestring;
            const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;

            if (strcmp(cjson_req, "showList") == 0) {
                send_showListToClient(client, cjson_name);
                /*
                printf("client %s request list\n", client -> name);
                //pthread_mutex_lock(&clients_mutex);


                cJSON *response = cJSON_CreateObject();
                cJSON *nameList = cJSON_CreateArray();
                cJSON *stateList = cJSON_CreateArray();

                // 創建 JSON 響應
                cJSON_AddStringToObject(response, "type", "showList");

                for (int i = 0; i < MAX_EVENTS; i++) {
                    if (clients[i] && clients[i]->state != STATE_NOT_LOGGED_IN && strcmp(clients[i]->name, cjson_name) != 0) {
                        // 加入 name 和 state 到各自的 Array
                        cJSON_AddItemToArray(nameList, cJSON_CreateString(clients[i]->name));
                        if (clients[i]->state == STATE_IN_GAME) {
                            cJSON_AddItemToArray(stateList, cJSON_CreateString("gaming"));
                        }
                        else if (clients[i]->state == STATE_IN_WAITING) {
                            cJSON_AddItemToArray(stateList, cJSON_CreateString("waiting"));
                        }
                    }
                }
                //pthread_mutex_unlock(&clients_mutex);


                // 完成後將 nameList 和 stateList 添加到 response JSON 中
                cJSON_AddItemToObject(response, "nameList", nameList);
                cJSON_AddItemToObject(response, "stateList", stateList);
                // 轉換為字串並發送
                char *json_string = cJSON_PrintUnformatted(response);
                //printf("%s\n", json_string);
                send(client_fd, json_string, strlen(json_string), 0);
                printf("send list to player %s\n", client -> name);
                // 清理記憶體
                free(json_string);
                cJSON_Delete(response);
                
            }
            
        }
    }
    return NULL;
}
*/