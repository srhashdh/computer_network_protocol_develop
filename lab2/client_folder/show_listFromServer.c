#include "define.h"
void show_listFromServer(cJSON *cjson){
    
    cJSON *nameList = cJSON_GetObjectItem(cjson, "nameList");
    cJSON *stateList = cJSON_GetObjectItem(cjson, "stateList");
    int len = cJSON_GetArraySize(nameList);
    if(cJSON_IsArray(nameList) && cJSON_IsArray(stateList)){
        int name_listLen = cJSON_GetArraySize(nameList);
        int state_listLen = cJSON_GetArraySize(stateList);
        if(name_listLen == state_listLen){
            for(int i = 0; i < name_listLen; i++){
                cJSON* name = cJSON_GetArrayItem(nameList, i);
                cJSON* state = cJSON_GetArrayItem(stateList, i);
                const char *name_str = cJSON_GetStringValue(name);
                const char *state_str = cJSON_GetStringValue(state);
                printf("player %s  is %s\n", name_str, state_str);
            }
        }
    }
    printf("show list success\n");
}