#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <unistd.h>
#include<stdlib.h> //atoi

#define OP_START '\x02'
#define OP_STOP 'x'
struct message {
    char servermessage[150];
}message;
char *changecommand(char *text);
int main(int argc , char *argv[])
{
    int socket_desc, lengthofmessage, index = 0, index1 = 0;
    struct sockaddr_in server;
    char message[2000], server_reply[2000], word_copy_message[150];
    int potnumber_client;
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
        lengthofmessage = strlen(message);
        struct message message_box[10000];
        for(int i = 0; i <= lengthofmessage; i++) {
            if(message[i] == ' ' || i == lengthofmessage) {
                strcpy(message_box[index1].servermessage, word_copy_message);
                index = 0;
                index1 += 1;
                memset(word_copy_message, 0, 150);
            } else {
                word_copy_message[index] = message[i];
                index += 1;
            }
        }
        char *messagereturn;
        messagereturn = malloc(150 * sizeof(char));
        //check command
        if(strcmp(message_box[0].servermessage, "/shell") == 0) {
            for(int i = 1; i <= (index1 - 1); i++) {
                strcpy(message_box[0].servermessage, message_box[0+i].servermessage);
            }
            index1 -= 1;
        }
        messagereturn = changecommand(message_box[0].servermessage);
        //combine all message_box
        strcpy(message, messagereturn);
        for(int i = 0; i < (index1 -1); i++) {
            if(i != (index-2)) {
                strcat(message, " ");
            }
            strcat(message, message_box[i+1].servermessage);
        }
        index1 = 0;
	    FILE *fp;
	    fp = fopen("server-message.txt", "w");
        fputs(message, fp);
	    fclose(fp);
        //Send to server
        //After Client has recieve form server, Client write message back to server
        printf("--- Sending init --- \n");
        char tmp[250],buf[250], messageget[250];
        //use popen in order to pointer to the first memory location that hold the results (results ---> value of message)
        fp = fopen("server-message.txt", "r");
        fgets(messageget, 250, fp);
        fp = popen(messageget, "r");
        {
            //fgets use to read next input line to keep in charactor array with value MAXLINE - 1
            while (fgets(buf, 2, fp))
            {
            printf("%s:",buf);
            //If write(socket_desc , buf , strlen(buf)) < 0 it means client didn't send anything to server
            if( write(socket_desc , buf , strlen(buf)) < 0)
            {
                printf("Send failed");
                return 1;
            }
            bzero(message,200);
            bzero(tmp,200);
            bzero(buf,200);
            }
        }
	    fclose(fp);
        //Stop sending
        //After Client send message to server
        printf("Stop sent..\n");
        usleep(1000000); //1second
        sprintf(message,"%c",OP_STOP);
        printf("%s",message);
        if( write(socket_desc , message ,2) < 0)
        {
            printf("Send failed");
            return 1;
        }
        bzero(message,2000);
        bzero(tmp,200);
    }
        
    printf("\n");
     
}
char *changecommand(char *text) {
        if((strcmp(text, "/mv") == 0)) {
            strcpy(text, "mv");
        } else if ((strcmp(text, "/rm") == 0)) {
            strcpy(text, "rm");
        } else if((strcmp(text, "/mkdir") == 0)) {
            strcpy(text, "mkdir");
        } else if((strcmp(text, "/cp") == 0)) {
            strcpy(text, "cp");
        } 
        return text;
}
