#include "define.h"

void broadcast_toClients(char *player, char *state) {
    // 创建 JSON 对象
    cJSON *cjson = cJSON_CreateObject();
    if (cjson == NULL) {
        printf("Failed to create JSON object\n");
        return;
    }

    // 添加 player 和 state 字段
    cJSON_AddStringToObject(cjson, "player", player);
    cJSON_AddStringToObject(cjson, "state", state);
    
    // 打印为字符串
    char *json_string = cJSON_PrintUnformatted(cjson);
    if (json_string == NULL) {
        printf("Failed to print JSON string\n");
        cJSON_Delete(cjson);
        return;
    }

    // 遍历 clients，发送消息
    for (int i = 0; i < MAX_EVENTS; i++) {
        if (clients[i] != NULL && clients[i]->state == STATE_IN_WAITING) {
            // 发送 JSON 字符串
            send(clients[i]->fd, json_string, strlen(json_string), 0);
        }
    }

    // 释放资源
    free(json_string);
    cJSON_Delete(cjson);
}
