#include "json_helper.h"

void get_telegram_chat(struct telegram_chat *chat, char *json){
    // char *target1 = "\"chat\"";
    char *target_id = "\"id\"";
    char *target_text = "\"text\"";
    char *index1, *index2;

    // index1 = strstr(json, target1);
    index2 = strstr(json, target_id);

    while(index2 != NULL){
        index2 = strstr(json, target_id);
        index2 += strlen(target_id) + 1;
        int i = 0;
        while(*(index2 + i) != ','){
            chat->id[i] = *(index2 + i);
            i++;
        }

        break;
    }

    index2 = strstr(json, target_text);
    while(index2 != NULL){
        index2 = strstr(json, target_text);
        index2 += strlen(target_text) + 2;

        int i = 0;
        while(*(index2 + i) != '"'){
            chat->text[i] = *(index2 + i);
            i++;
        }

        break;
    }

}