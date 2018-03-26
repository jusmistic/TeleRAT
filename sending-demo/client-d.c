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
    //If cannot create socket it return value of socket_desc valuable = -1
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    //Connect to remote server
    //If cannot connect to server it return value of (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0 and end program
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect error");
        return 1;
    }
     
    printf("Connected\n");
    //Send some data (client --> server)
    while(1){
 
        //Receive a reply from the server(Server have massage to client and client read this message)
	//bzero(message,2000) --> set a byte string (message)
        bzero(message,2000);
        //If read(socket_desc, message , 2000 ) < 0 it means Server didn't send anything to client
        if( read(socket_desc, message , 2000 ) < 0)
        {
            printf("recieve failed");
        }printf("%s\n",message);
        
        //Send to server
        //After Client has recieve form server, Client write message back to server
        printf("--- Sending init --- \n");
        int i=0;
        char tmp[250],buf[250];
        //use popen in order to pointer to the first memory location that hold the results (results ---> value of message)
        FILE *fp = popen(message, "r");
        {
            //fgets use to read next input line to keep in charactor array with value MAXLINE - 1
            while (fgets(buf, 200, fp))
            {
            printf("%s\n:",buf);
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
        break;
    }
        
    printf("\n");
     
    return 0;
}
