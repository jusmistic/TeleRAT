#include "json_helper.h"

void get_telegram_chat(struct telegram_chat *chat, char *json){
    // char *target1 = "\"chat\"";
    char *target_id = "\"id\"";
    char *target_text = "\"text\"";
    char *index1, *index2;

    unsigned int i = 0;

    // printf("Size of chat->text %ld\n", sizeof(chat->text));
    // index1 = strstr(json, target1);
    memset(chat->id, 0, sizeof(chat->id));
    memset(chat->text, 0, sizeof(chat->text));

    index2 = strstr(json, target_id);
    i = 0;

    while(index2 != NULL){
        index2 = strstr(json, target_id);
        index2 += strlen(target_id) + 1;
        while(*(index2 + i) != ',' && i < (sizeof(chat->id) / sizeof(chat->id[0]))){
            chat->id[i] = *(index2 + i);
            i++;
        }

        // chat->id[i] = 0;

        break;
    }

    index2 = strstr(json, target_text);
    i = 0;

    while(index2 != NULL){
        index2 = strstr(json, target_text);
        index2 += strlen(target_text) + 2;
        while(*(index2 + i) != '"' && i < (sizeof(chat->text) / sizeof(chat->text[0]))){
            chat->text[i] = *(index2 + i);
            i++;
        }

        // chat->text[i] = 0;

        break;
    }

}