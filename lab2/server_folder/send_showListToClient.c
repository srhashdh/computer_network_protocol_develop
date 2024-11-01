#include "define.h"
void send_showListToClient(struct client_info *client, const char *cjson_name){
    printf("client %s request list\n", client -> name);
    pthread_mutex_lock(&clients_mutex);


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

    // 完成後將 nameList 和 stateList 添加到 response JSON 中
    cJSON_AddItemToObject(response, "nameList", nameList);
    cJSON_AddItemToObject(response, "stateList", stateList);
    // 轉換為字串並發送
    char *json_string = cJSON_PrintUnformatted(response);
    //printf("%s\n", json_string);
    send(client -> fd, json_string, strlen(json_string), 0);
    printf("send list to player %s, %d\n", client -> name, client -> fd);
    // 清理記憶體
    free(json_string);
    cJSON_Delete(response);
    pthread_mutex_unlock(&clients_mutex);

}