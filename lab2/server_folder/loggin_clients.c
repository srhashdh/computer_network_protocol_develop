#include "define.h"


void loggin_clients(int epoll_fd, int server_fd) {
    struct epoll_event events[MAX_EVENTS];

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == server_fd) {
                // 接受新连接
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

                // 分配内存并存储客户端信息
                struct client_info *client = malloc(sizeof(struct client_info));
                client->fd = client_fd;
                client->addr = client_addr;
                client->name[0] = '\0';
                client->state = STATE_NOT_LOGGED_IN; // 设置为未登录状态

                for (int j = 0; j < MAX_EVENTS; j++) {
                    if (!clients[j]) {
                        clients[j] = client;
                        break;
                    }
                }
                struct epoll_event event;
                event.events = EPOLLIN;
                event.data.ptr = client;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
            } else {
                // 处理客户端信息
                struct client_info *client = (struct client_info *)events[i].data.ptr;
                char message[BUFFER_SIZE];
                int valread = read(client->fd, message, BUFFER_SIZE);

                if (valread > 0) {
                    message[valread] = '\0'; // 确保字符串以 null 结尾
                    // 解析 JSON
                    cJSON *cjson = cJSON_Parse(message);
                    if (cjson == NULL) {
                        printf("Parsed error\n");
                        return;
                    }

                    const char *cjson_req = cJSON_GetObjectItem(cjson, "request")->valuestring;
                    if (strcmp(cjson_req, "loggin") == 0) {
                        bool name_taken = false;
                        const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;

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
                            client->state = STATE_IN_WAITING; // 登录成功后更改状态
                            printf("Player %s logged in\n", client->name);
                            cJSON_AddStringToObject(response, "loggin", "success");
                        } else {
                            cJSON_AddStringToObject(response, "loggin", "fail");
                        }
                        char *json_string = cJSON_PrintUnformatted(response);
                        send(client->fd, json_string, strlen(json_string), 0);
                        free(json_string);
                        cJSON_Delete(response);
                    } else if (client->state == STATE_IN_WAITING) {
                        // 处理已登录客户端的命令或操作
                    }
                    cJSON_Delete(cjson); // 删除解析的 JSON 对象
                } else {
                    // 处理断开连接
                    printf("Player %s disconnected\n", client->name);
                    char *offline_client = client->name;
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client->fd, NULL);
                    close(client->fd);

                    // 释放内存
                    for (int j = 0; j < MAX_EVENTS; j++) {
                        if (clients[j] == client) {
                            free(client);
                            clients[j] = NULL;
                            break;
                        }
                    }
                    broadcast_toClients(offline_client, "offline");
                }
            }
        }
    }
}
