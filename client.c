#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <unistd.h>
#include<stdlib.h>
 
int main(int argc , char *argv[])
{
    int socket_build;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];
     
    //Create socket = socket_build
    //if cannot create socket it means socket_build valuable = -1
    socket_build = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_build == -1)
    {
        printf("Could not create socket");
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    //Connect to remote server
    //if cannot connect printf connect error and end program
    //if can connect printf connected
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect error");
        return 1;
    }
     
    printf("Connected\n");
    //Send some data to server
    while(1){
 
        //Receive a reply from the server(Server have massage to client and client read this massage)
        bzero(message,2000);
        printf("client read:");
        if( read(socket_desc, message , 2000 ) < 0)
        {
            printf("recv failed");
        }
        printf("%s\n",message);
        bzero(message,2000);
        //client send massage back to server after receive reply form server
        printf("client write:");
        scanf("%s",message);
        if( write(socket_desc , message , strlen(message)) < 0)
        {
            printf("Send failed");
            return 1;
        }
        bzero(message,2000);     
        }
        
    printf("\n");
     
    return 0;
}
