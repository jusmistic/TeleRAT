#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write




int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
    char message[2000];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    printf("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
    int ret;
    char temp[2000];
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        printf("Connection accepted");
         while(1)
        {
        //Reply to the client
            printf("\nServer Write: ");
            bzero(message,2000);
            strcpy(message,"\x01");
            scanf("%s",temp);
            strcpy(message,temp);
            if(write(new_socket , message , strlen(message))<0)
            {
                  printf("Sending Error!\n");
            }
            printf("Sent");
            //Clear message Var  
            bzero(message,2000);
            printf("\nServer Read: ");
            if( ret = read(new_socket, message, 2000) < 0)
            {
                printf("Recv Error!\n");                
            }
            printf("%s",message);
            bzero(message,2000);

        }
        
    }
     
    if (new_socket<0)
    {
        printf("accept failed");
        return 1;
    }
     
    return 0;
}