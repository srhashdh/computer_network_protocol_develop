void handle_clientRequest(){
    while(1){
      int valread = read(client->fd, message, BUFFER_SIZE);
      char message[BUFFER_SIZE];
      if(valread > 0){
        message[valread] = '\0';
        cJSON *cjson = cJSON_Parse(message);
        if (cjson == NULL) {
            printf("Parsed error\n");
            return;
        }
        const char *cjson_req = cJSON_GetObjectItem(cjson, "request") -> valuestring;
        const char *cjson_name = cJSON_GetObjectItem(cjson, "name") -> valuestring;
        if(strcmp(cjson_req, "showList") == 0){

          memset(client_nameList, 0, sizeof(client_nameList));
          cJSON* cjson = NULL;
          cJSON* nameList = NULL;
          cJSON* stateList = NULL;
          cJSON = cJSON_CreateObject();
          cJSON_AddStringToObject(cjson, "type", "showList");
          nameList = cJSON_CreateArray();
          stateList = cJSON_CreateArray();


          for (int i = 0; i < MAX_EVENTS; i++) {
              if (clients[i] && clients[i] -> state != STATE_NOT_LOGGED_IN && strcmp(clients[i] -> name, cjson_name) != 0) {
                  
                  cJSON_AddItemToArray(nameList, cJSONCreateString(clients[i] -> name));
                  if(clients[i] -> state == STATE_IN_GAME){
                    cJSON_AddItemToArray(stateList, cJSONCreateString("gaming"));
                  }
                  else if(clients[i] -> state == STATE_IN_WAITING){
                    cJSON_AddItemToArray(stateList, cJSONCreateString("waiting"));
                  }
              }
              cJSON_AddItemToObject(cjson, "nameList", nameList);
              cJSON_AddItemToObject(cjson, "stateList", stateList);
              char *json_string = cJSON_PrintUnformatted(cjson);
              send(client -> fd, json_string, strlen(json_string), 0);
          }
        }
      }
    }
}