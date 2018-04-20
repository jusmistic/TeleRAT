#include "include/common.h"
#include "include/util.h"

#include "tcp_server.h"
#include "Telegram/telegram.h"
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
    char hostname[256];
    Telegram_chat chat;
}sendto_function[100];

struct user_select{
    char chat_id[ID_LENGTH];
    int client_soc;
}user_select[100];

int n = 0, user_select_n = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *recvmg(void *sock)
{
	struct sendto_function cl = *((struct sendto_function *)sock);
	char msg[500];
	int len;
    char status[3];
    int select = -1;
    if((len = recv(cl.client_soc, msg, 500, 0)) > 0){
        for(int i = 0; i < n; i++){
            if(sendto_function[i].client_soc == cl.client_soc){
                select = i;
                break;
            }
        }
        //Copy hostname
        strcpy(sendto_function[select].hostname, msg);

        while((len = recv(cl.client_soc, msg, 500, 0)) > 0){
            // printf("[Thread %d] recv: %s\n", cl.client_soc, msg);
            write(cl.client_soc, "0", sizeof(status));

            //Check index of socket array.
            for(int i = 0; i < n; i++){
                if(sendto_function[i].client_soc == cl.client_soc){
                    select = i;
                    break;
                }
            }
            
            pthread_mutex_lock(&mutex);
            if(telegram_check(&sendto_function[select].chat) > 0){
                write(cl.client_soc, "1", sizeof(status));
                printf("[Sending to client %d]\n", sendto_function[select].client_soc);
                if((len = write(cl.client_soc, sendto_function[select].chat.id, sizeof(sendto_function[select].chat.id))) > 0) {
                    printf("chat id: %s\n", sendto_function[select].chat.text);
                    
                }
                if((len = write(cl.client_soc, sendto_function[select].chat.text, sizeof(sendto_function[select].chat.text))) > 0) {
                    printf("msg: %s\n", sendto_function[select].chat.text);
                    
                }
                telegram_mark_send(&sendto_function[select].chat);
                printf("[End sending]\n");
            }
            pthread_mutex_unlock(&mutex);
        }
    }
    
    pthread_mutex_lock(&mutex);
    /* delete client socket on disconected */
    printf("%s disconnected\n",cl.ip_client);

    for(int i = 0; i < user_select_n; i++){
        if(user_select[i].client_soc == cl.client_soc){
            char temp[350];
            sprintf(temp, "Client `%s` is disconnect.", sendto_function[select].hostname);
            telegram_send_msg(user_select[i].chat_id, temp);
        }
    }

    for(int i = 0; i < n; i++) {
        if(sendto_function[i].client_soc == cl.client_soc) {
            int j = i;
            while(j < n-1) {
                sendto_function[j] = sendto_function[j+1];
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
    int socket_desc , client_sock , new_sock;
    int max_sd, sd, activity;
    struct sockaddr_in server, client;
    struct timeval tv = {30, 0};
    pthread_t server_serv;
    fd_set readfds;
    
    //Create socket
    //If cannot create socket it return value of socket_desc valuable = -1
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
     
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
    socklen_t socket_size = sizeof(client);
    while(1) {
		if((new_sock = accept(socket_desc,(struct sockaddr *)&client, &socket_size)) < 0) {
			perror("accept unsuccessful");
			exit(1);
		}

        setsockopt(new_sock, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));

		pthread_mutex_lock(&mutex);

        char ip[INET_ADDRSTRLEN];
        strcpy(ip, inet_ntoa(client.sin_addr));
		// inet_ntop(AF_INET, (struct sockaddr *)&client, ip, INET_ADDRSTRLEN);
		printf("[Bot] %s connected\n",ip);

		sendto_function[n].client_soc = new_sock;
		strcpy(sendto_function[n].ip_client, ip);
        int socket = n;

		pthread_create(&server_serv, NULL, recvmg, &sendto_function[n]);
        n++;

		pthread_mutex_unlock(&mutex);
	}

    return 0;
}

void *bot_thread(void * argc){
    int *portnumber;
    portnumber = (int *) argc;
    botserver(*portnumber);
}

void *command(){
    while(1){
        if(telegram_check(&chat) > 0){
            int select = -1;
            printf("Client list%d\n", n);
            pthread_mutex_lock(&mutex);

            for(int i = 0; i < n; i++){
                if(strcmp(user_select[i].chat_id, chat.id) == 0){
                    select = i;
                    printf("found %d\n", select);
                    break;
                }
            }

            if(strncmp(chat.text, "/help", 5) == 0){
                char *help_text = help();
                telegram_send_msg(chat.id, help_text);
            }
            else if(strncmp(chat.text, "/list", 5) == 0){
                char *text = (char *) malloc(256);
                char *temp = (char *) malloc(256);
                memset(text, 0, sizeof(text));

                if(n > 0){
                    int i = 0;
                    for(i; i < n; i++){
                        memset(temp, 0, sizeof(temp));
                        sprintf(temp,   "%d) %s\n"
                                        "ip : %s\n", 
                                        (i+1), sendto_function[i].hostname ,sendto_function[i].ip_client);
                        strcat(text, temp);
                    }

                    memset(temp, 0, sizeof(temp));
                    strcpy(temp, text);

                    memset(text, 0, sizeof(text));
                    sprintf(text,   "Have %d client(s) connect to server\n"
                                    "```\n%s```\n"
                                    "Use /select <id> to select the client."
                                    , n, temp);

                    telegram_send_msg(chat.id, text);
                }
                else{
                    telegram_send_msg(chat.id, "No client connected.");
                }

                free(temp);
                free(text);
            }
            else if(strncmp(chat.text, "/select", 7) == 0){
                char temp[100] = "";
                int user_select_id;
                for(int i = 7; chat.text[i] != 0; i++){
                    temp[i-7] = chat.text[i];
                }

                if(strlen(temp) > 0){
                    user_select_id = atoi(temp);
                    if(user_select_id > 0){
                        if(select != -1){
                            user_select[select].client_soc = sendto_function[user_select_id-1].client_soc;
                            printf("[Debug] It already have (%d)(socket %d)\n", select, sendto_function[user_select_id-1].client_soc);
                        }else{
                            select = user_select_n;
                            strcpy(user_select[select].chat_id, chat.id);
                            user_select[select].client_soc = sendto_function[user_select_id-1].client_soc;
                            user_select_n++;
                            printf("[Debug] create new one (%d)(socket %d)\n", select, sendto_function[user_select_id-1].client_soc);
                        }
                        telegram_mark_send(&chat);

                        sendto_function[user_select_id-1].chat = chat;
                        printf("Debug => %s\n", sendto_function[user_select_id-1].chat.id);
                        printf("Debug => %d\n", sendto_function[user_select_id-1].client_soc);
                        sprintf(temp, "Selected client %d", user_select_id);
                        telegram_send_msg(chat.id, temp);
                    }
                    else{
                        telegram_send_msg(chat.id, "Invalid value.");
                    }
                }
                else{
                    telegram_send_msg(chat.id, "Please give id of client.");
                }

            }
            else if(select < 0){
                telegram_send_msg(chat.id,  "You doesn't select the client.\n"
                                            "Use /list to show avaliable clients.\n"
                                            "Use /select to select the cliend");
            }
            else{
                int temp_socket = -1;
                int is_found = 0;
                for(int i = 0; i < user_select_n; i++){
                    if(strcmp(user_select[i].chat_id, chat.id) == 0){
                        temp_socket = user_select[i].client_soc;
                        break;
                    }
                }
                
                for(int i = 0; i < n; i++){
                    if(sendto_function[i].client_soc == temp_socket){
                        sendto_function[i].chat = chat;
                        is_found = 1;
                        break;
                    }
                }

                if(is_found == 0){
                    telegram_send_msg(chat.id,  "Client disconnected.\n"
                                                "Use /list to view avaliable clients.\n"
                                                "Use /select to select client.");
                }
            }

            telegram_mark_send(&chat);

            pthread_mutex_unlock(&mutex);
        }
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
    pthread_t tid[3];

    int potnumber_server;
    potnumber_server = atoi(argv[1]); 
    if (2 != argc) {

        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);

    }

    if(pthread_create(&tid[0], NULL, command, NULL) < 0){
        perror("Can't create thread for command\n");
    }
    printf("Thread for command.\n");

    if(pthread_create(&tid[1], NULL, telegram_serv, NULL) < 0){
        perror("Can't create thread for Telegram\n");
    }
    printf("Thread for telegram created.\n");

    if(pthread_create(&tid[2], NULL, bot_thread, (void *)&potnumber_server) < 0){
        perror("Can't create thread for Bot\n");
    }
    printf("Thread for Bot.\n");

    for(int i = 0; i < 3; i++){
        pthread_join(tid[i], NULL);
    }
}