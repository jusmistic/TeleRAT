#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#define OP_START '\x02'
#define OP_STOP 'x'


int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
    char message[2000]="";
     
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
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        printf("Connection accepted");
        // while(1)
        // {
        //Reply to the client
            printf("\nServer Write: ");
            bzero(message,2000);
            scanf(" %s",message);
            printf("%s",message);
            if(ret = write(new_socket , message , strlen(message))<0)
            {
                  printf("Sending Error!\n");
            }
            printf("Sent\n");
            //Clear message Var 
            bzero(message,2000);
            printf("Server Read\n");
            int i =0;
            while(1)
            {
                bzero(message,200);
                // printf("Start Sending\n");
                if(read(new_socket, message, 200) < 0)
                {
                    printf("Recv Error!\n");                
                }
                // message[strlen(message)] ='\0';
                printf("%s i:%d\n",message,i);
                if(message[0] == 'x')
                {
                    printf("Exit..");
                    return 1;
                }                
                i++;
            }
            printf("Stop Recieve...\n");
            return 1;

        // }
        
    }
     
    if (new_socket<0)
    {
        printf("accept failed");
        return 1;
    }
     
    return 0;
}