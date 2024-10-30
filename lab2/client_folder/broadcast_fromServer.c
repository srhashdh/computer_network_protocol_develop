#include "define.h"

void *broadcast_fromServer(void *args) {
    int server_fd = *(int *) args;

    while (1) {
        char buffer[BUFFER_SIZE];
        // 接收数据
        int bytes_received = recv(server_fd, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received > 0) {
            // 确保字符串以 null 结尾
            buffer[bytes_received] = '\0';

            // 解析 JSON
            cJSON *cjson = cJSON_Parse(buffer);
            if (cjson == NULL) {
                printf("Parsed error: %s\n", cJSON_GetErrorPtr());
                continue; // 如果解析失败，继续接收下一条消息
            }

            // 获取 player 和 state 字段
            const char *cjson_player = cJSON_GetObjectItem(cjson, "player")->valuestring;
            const char *cjson_state = cJSON_GetObjectItem(cjson, "state")->valuestring;

            // 检查获取的字符串是否有效
            if (cjson_player && cjson_state) {
                printf("Update from server: player %s %s\n", cjson_player, cjson_state);
            } else {
                printf("Player or state not found in JSON\n");
            }

            // 释放 JSON 对象
            cJSON_Delete(cjson);
        } else if (bytes_received == 0) {
            // 连接关闭的处理
            printf("Server closed the connection\n");
            break; // 退出循环
        } else {
            // 错误处理
            perror("recv failed");
            break; // 退出循环
        }
    }

    return NULL;
}
