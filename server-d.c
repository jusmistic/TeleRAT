#include "include/common.h"
#include "tcp_server.h"
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <pthread.h>

#define OP_START '\\x02'
#define OP_STOP "\x03"

Telegram_chat chat;

void *connect_handle(void * temp_struct);
void *telegram_serv(void *vargp);

struct sendto_function {
    int client_soc;
    char ip_client[INET_ADDRSTRLEN];
}sendto_function;

int clients[100];
int n = 0;
int wow;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *recvmg(void *sock)
{
	struct sendto_function cl = *((struct sendto_function *)sock);
	char msg[500];
	int len;
	int i;
	int j;
    char status[3];
    while((len = recv(cl.client_soc,msg,500,0)) > 0){
        // sprintf(status, "%d", telegram_check(&chat));
        // printf("status: %s\n", status);
        write(cl.client_soc, "0", sizeof(status));
        if(telegram_check(&chat) > 0){
            write(cl.client_soc, "1", sizeof(status));
            printf("pinggg!!\n");
            pthread_mutex_lock(&mutex);
            if((len = write(cl.client_soc, chat.id, sizeof(chat.id))) > 0) {
                printf("chat id: %s\n", chat.text);
                
            }
            if((len = write(cl.client_soc, chat.text, sizeof(chat.text))) > 0) {
                printf("msg: %s\n", chat.text);
                
            }
            telegram_mark_send(&chat);
            pthread_mutex_unlock(&mutex);
        }
    }
    printf("len = %d\n", len);
    pthread_mutex_lock(&mutex);
    printf("%s disconnected\n",cl.ip_client);
    for(i = 0; i < n; i++) {
        if(clients[i] == cl.client_soc) {
            j = i;
            while(j < n-1) {
                clients[j] = clients[j+1];
                j++;
            }
            break;
        }
    }
    n--;
    pthread_mutex_unlock(&mutex);
}

int botserver(int potnumber_server)
{
    int socket_desc , client_sock , new_sock, server_i = 0, max_clients = 30,client_socket[30];
    int max_sd, sd, activity;
    struct sockaddr_in server , client;
    pthread_t server_serv;
    fd_set readfds;
    char *message = "ECHO Daemon v1.0 \r\n";
    
    //Create socket
    //If cannot create socket it return value of socket_desc valuable = -1
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    for (int i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
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
    if(listen(socket_desc,5) != 0) {
		perror("listening unsuccessful");
		exit(1);
	}
     
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    // c = sizeof(struct sockaddr_in);
    // struct sendto_function send_to_function;
    socklen_t socket_size = sizeof(client);
    while(1) {
		if((new_sock = accept(socket_desc,(struct sockaddr *)&client, &socket_size)) < 0) {
			perror("accept unsuccessful");
			exit(1);
		}
		pthread_mutex_lock(&mutex);
        char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, (struct sockaddr *)&client, ip, INET_ADDRSTRLEN);
		printf("%s connected\n",ip);
		sendto_function.client_soc = new_sock;
		strcpy(sendto_function.ip_client,ip);
		clients[n] = new_sock;
		n++;
		pthread_create(&server_serv, NULL, recvmg, &sendto_function);
		pthread_mutex_unlock(&mutex);
	}

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
    int new_socket = socket_struct.client_soc;
    char message[2000]="", message_check[3] = "";
    int ret, read_socket;
    char buf[3], *ipclient = socket_struct.ip_client;
    int read_size;
    while(1){
        bzero(buf,sizeof(buf));
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
            if(ret = recv(new_socket, buf, 3, 0) <= 0){
                printf("Client %d disconnected \n", new_socket);
                close(new_socket);
                fflush(stdout);
                pthread_exit(NULL);
                return 0;
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