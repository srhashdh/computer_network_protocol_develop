#include "define.h"
void broadcast_fromServer(cJSON *cjson){

    
    const char *cjson_player = cJSON_GetObjectItem(cjson, "player") -> valuestring;
    const char *cjson_state = cJSON_GetObjectItem(cjson, "state") -> valuestring;
    
    if (cjson_player && cjson_state) {
        printf("Update from server: player %s %s\n", cjson_player, cjson_state);
                    
    }
            
    else {
        printf("Player or state not found in JSON\n");
    }
                
}