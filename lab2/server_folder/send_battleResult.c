#include "define.h"

void send_battleResult(struct client_info *client, cJSON *cjson){
    const char *cjson_rival = cJSON_GetObjectItem(cjson, "rival")->valuestring;
    const char *cjson_name = cJSON_GetObjectItem(cjson, "name")->valuestring;
    int cjson_choice = cJSON_GetObjectItem(cjson, "choice")->valueint;
    int rival_fd;
    int rival_choice;
    bool flag = true;
    int i;
    while(flag){
      for(i = 0; i < MAX_EVENTS; i++){
          if(clients[i] && strcmp(clients[i] -> name, cjson_rival) == 0 && clients[i] -> battle_res == true){
              rival_fd = clients[i] -> fd;
              rival_choice = clients[i] -> choice;
              flag = false;
              break;
          }
      }
    }
    cJSON *response = cJSON_CreateObject();
    cJSON_AddStringToObject(response, "name", cjson_name);
    cJSON_AddStringToObject(response, "rival", cjson_rival);
    cJSON_AddStringToObject(response, "type", "battle");
    
    if(client -> choice == rival_choice){
        cJSON_AddStringToObject(response, "result", "tie");
        printf("player: %s and player: %s tie\n", client -> name, cjson_rival);
    }
    else if((client -> choice - rival_choice + 3) % 3 == 1){
        cJSON_AddStringToObject(response, "result", "win");
        printf("player: %s win, player: %s lose\n", client -> name, cjson_rival);
    }
    else{
        cJSON_AddStringToObject(response, "result", "lose");
        printf("player: %s lose, player: %s win\n", client -> name, cjson_rival);
    }
    char *json_string = cJSON_PrintUnformatted(response);
    
    send(client -> fd, json_string, strlen(json_string), 0);
    printf("send result to player %s, %d\n", client -> name, client -> fd);
    char *str = NULL;
    str = cJSON_Print(response);
    printf("json: %s\n", str);
    free(json_string);
    cJSON_Delete(response);
    clients[i] -> state = STATE_IN_WAITING;
    clients[i] -> battle_res = false;
    client -> state = STATE_IN_WAITING;
    clients[i] -> battle_res = false;
}