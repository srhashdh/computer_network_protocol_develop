#include "define.h"

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
void connect_toClients(int epoll_fd, int server_fd) {
    struct epoll_event events[MAX_EVENTS];

    while (1) {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; i++) {
            if (events[i].data.fd == server_fd) {
                
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
                set_nonblocking(client_fd);
                
                struct client_info *client = malloc(sizeof(struct client_info));
                client->fd = client_fd;
                client->addr = client_addr;
                client->name[0] = '\0';
                client->state = STATE_NOT_LOGGED_IN; 

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
                
                pthread_t client_thread;
                pthread_create(&client_thread, NULL, handle_clientRequest, (void *)client);
                pthread_detach(client_thread);
            }
            /*
            else {
                
                struct client_info *client = (struct client_info *)events[i].data.ptr;
                
                pthread_t client_thread;
                pthread_create(&client_thread, NULL, handle_clientRequest, (void *)client);
                pthread_detach(client_thread);
                    //handle_clientRequest(client);
                
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
                            client->state = STATE_IN_WAITING; // 登录成功后更改状态
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
                    
//                    if (client->state == STATE_IN_WAITING) {
                        // 处理已登录客户端的命令或操作
//                        printf("play %s is waiting\n", client -> name);
//
//                        pthread_t client_thread;
//                        pthread_create(&client_thread, NULL, handle_clientRequest, (void *)client);
//                        pthread_detach(client_thread);
                        //handle_clientRequest(client);
//                    }
                    
                    cJSON_Delete(cjson); // 删除解析的 JSON 对象
                }
                
                else {
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
                
                if (client->state == STATE_IN_WAITING) {
                    // 处理已登录客户端的命令或操作
                    printf("play %s is waiting\n", client -> name);

                    pthread_t client_thread;
                    pthread_create(&client_thread, NULL, handle_clientRequest, (void *)client);
                    pthread_detach(client_thread);
                    //handle_clientRequest(client);
                }
                
            }
            */
        }
    }
}
