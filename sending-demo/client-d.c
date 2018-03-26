#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <unistd.h>
#include<stdlib.h>

#define OP_START '\x02'
#define OP_STOP 'x'
int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect error");
        return 1;
    }
     
    printf("Connected\n");
    //Send some data
    while(1){
 
        //Receive a reply from the server
        bzero(message,2000);
        if( read(socket_desc, message , 2000 ) < 0)
        {
            printf("recv failed");
        }printf("%s\n",message);
        
        //Send to server
        // bzero(message,2000);
        printf("--- Sending init --- \n");
        int i=0;
        char tmp[250],buf[250];
        FILE *fp;
        if ((fp = popen(message,"r")) != 0)
        {
            while (fgets(buf, 200, fp) != 0)
            {
                // fputs(buf, stdout); //Use when you want to print string
                // strcat(text,buf); //include stream to text
            // sprintf(buf,"%c%s",OP_START,buf);
            printf("%s\n:",buf);
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

        // while(i < 5)
        // {
        //     //init sending
        //     // scanf(" %[^\n]",temp);
        // //     sprintf(message,"%c%d",OP_START,i);
        // //     printf("%s\n:",message);
        // //     if( write(socket_desc , message , strlen(message)) < 0)
        // //     {
        // //         printf("Send failed");
        // //         return 1;
        // //     }
        // // bzero(message,200);
        // // bzero(tmp,200);
        // i++;
        // }
        //Stop sending
        printf("Stop sent..\n");
        usleep(1000000); //1sec
        sprintf(message,"%c",OP_STOP);
        printf("%s",message);
        if( write(socket_desc , message ,2) < 0)
        {
            printf("Send failed");
            return 1;
        }
        bzero(message,2000);
        bzero(tmp,200);
        break;
    }
        
    printf("\n");
     
    return 0;
}