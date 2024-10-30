void request_listFromServer(){
  cJSON *cjson = NULL;
  char* str = NULL;
  cjson = cJSON_CreateObject();
  cJSON_AddStringToObject(cjson, "request", "showList");
  cJSON_AddStringToObject(cjson, "name", info -> name);
  char *json_string = cJSON_PrintUnformatted(cjson);
  send(info -> fd, json_string, strlen(json_string), 0);
  //receive
}