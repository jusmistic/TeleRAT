#include "include/common.h"
#include "tcp_server.h"
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h>

#define OP_START '\\x02'
#define OP_STOP "\x03"

Telegram_chat chat;

void *connect_handle(void * temp_struct);
void *telegram_serv(void *vargp);

struct sendto_function {
    int *client_soc;
    char *ip_client;
}sendto_function;

int i = 100;

int wow;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int botserver(int potnumber_server)
{
    int socket_desc , client_sock , c, *new_sock, server_i = 0;
    struct sockaddr_in server , client;
    pthread_t server_serv;
    
    //Create socket
    //If cannot create socket it return value of socket_desc valuable = -1
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(potnumber_server);

    //Bind
    //bind() associates the socket with its local address [that's why server side binds, so that clients can use that address to connect to server.] connect() is used to connect to a remote [server] address
    while(1){
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
            puts("bind failed");
        }
        else{
            printf("bind done");
            break;
        }
        sleep(15);
    }
     
    //Listen
    //Waiting connection form client
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
    struct sendto_function send_to_function;
    
    while(1){
        if((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) < 0)
        {
            printf("accept failed");
            return 1;
        }
        // pthread_mutex_lock(&mutex);
        send_to_function.ip_client = inet_ntoa(client.sin_addr);
        send_to_function.client_soc = malloc(sizeof *send_to_function.client_soc);
        *send_to_function.client_soc = client_sock;
        if( pthread_create( &server_serv , NULL ,  connect_handle , (void*) &send_to_function) < 0)
        {
            perror("could not create thread");
            return 1;
        }
    }

    printf("It join now!\n");

    return 0;
}

void *bot_thread(void * argc){
    int *portnumber;
    portnumber = (int *) argc;
    botserver(*portnumber);
}


void *connect_handle(void * temp_struct){
    struct sendto_function socket_struct = *(struct sendto_function *) temp_struct;
    printf("Connection accepted\n");
    int new_socket = *socket_struct.client_soc;
    char message[2000]="";
    int ret, read_socket;
    char buf[256], *ipclient = socket_struct.ip_client;


    int read_size;
    while(1){
        pthread_mutex_lock(&mutex);
        if(telegram_check(&chat) > 0){
            telegram_mark_send(&chat);

            printf("[Start sending message to client]\n");
            printf("Chat id: %s\n", chat.id);
            printf("Chat text: %s\n", chat.text);
            printf("Client socket(%d) IP: %s\n", new_socket, ipclient);

            if(ret = write(new_socket, chat.id, 50) < 0){
                printf("Sending Error 1!\n");
                close(new_socket);
                // pthread_exit(&new_socket);
            }

            if(ret = write(new_socket , chat.text , 4000)<0)
            {
                printf("Sending Error 2!\n");
                close(new_socket);
                // pthread_exit(&new_socket);
            }
            if(ret = recv(new_socket, buf, sizeof(buf), 0) < 0){
                printf("recv failed\n");
                close(new_socket);
                // pthread_exit(&new_socket);
            }else{
                printf("OK!!!!!!!!!\n");
            }
            // pthread_mutex_unlock(&mutex);
            // sleep(3);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void *telegram_serv(void *vargp){
    telegram_init(&chat);
    while(1){
        if(tcp_server(&chat) <= 0){
            printf("Retry to bind address in 15 second...\n");
            sleep(15);
        }
    }
    pthread_exit(NULL);

    return NULL;
}

int main(int argc , char *argv[]){
    pthread_t tid;

    int potnumber_server;
    potnumber_server = atoi(argv[1]); 
    if (2 != argc) {

        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);

    }

    if(pthread_create(&tid, NULL, telegram_serv, NULL) < 0){
        perror("Can't create thread for Telegram\n");
    }
    printf("Thread for telegram created.\n");

    if(pthread_create(&tid, NULL, bot_thread, (void *)&potnumber_server) < 0){
        perror("Can't create thread for Bot\n");
    }
    printf("Thread for telegram Bot.\n");

    pthread_join(tid, NULL);
    // pthread_join(bot_thread, NULL);
}