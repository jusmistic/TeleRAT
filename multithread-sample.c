#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "tcp_server.h"

void *telegram_serv(void *vargp){
    tcp_server();

    return NULL;
}

void *telegram_serv2(){
    printf("Test\n");
    int i = 0;
    while(i < 5){
        printf("Thread 2 => %d\n", ++i);
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