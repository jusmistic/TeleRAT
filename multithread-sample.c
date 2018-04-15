#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "tcp_server.h"

Telegram_chat chat;

void *telegram_serv(void *vargp){
    tcp_server(&chat);

    return NULL;
}

void *telegram_serv2(void *vargp){
    while(1){
        if(strlen(chat.id) > 0){
            printf("[Telegram chat]\n");
            printf("chat id: %s\n", chat.id);
            printf("chat message: %s\n", chat.text);
            printf("[Telegram end chat]\n");

            telegram_send_msg(chat.id, chat.text);

            bzero(chat.id, sizeof(chat.id));
            bzero(chat.text, sizeof(chat.text));
        }
    }

    return NULL;
}

int main(){
    pthread_t tid;
    if(pthread_create(&tid, NULL, telegram_serv, NULL) < 0){
        perror("Can't create thread1");
    }
    if(pthread_create(&tid, NULL, telegram_serv2, NULL) < 0){
        perror("Can't create thread2");
    };
    pthread_exit(NULL);
    return 0;
}