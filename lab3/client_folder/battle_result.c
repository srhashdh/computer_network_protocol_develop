#include "define.h"

void battle_result(cJSON *cjson){
    const char *cjson_result = cJSON_GetObjectItem(cjson, "result") -> valuestring;
    if(strcmp(cjson_result, "tie") == 0){
        printf("result: tie\n");
    }
    else if(strcmp(cjson_result, "win") == 0){
        printf("you win\n");
    }
    else if(strcmp(cjson_result, "lose") == 0){
        printf("you lose\n");
    }
}