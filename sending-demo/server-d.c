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
    //If cannot create socket it return value of socket_desc valuable = -1
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
    //bind() associates the socket with its local address [that's why server side binds, so that clients can use that address to connect to server.] connect() is used to connect to a remote [server] address
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    printf("bind done");
     
    //Listen
    //Waiting connection form client
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
    int ret;
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        //accept connection form client complete
        printf("Connection accepted");
        //Reply to the client
            //Server send message to client
            printf("\nServer Write: ");
            bzero(message,2000);
            scanf(" %[^\n]",message);
            printf("%s",message);
	    //If write(new_socket , message , strlen(message) < 0 it means Server didn't send anything to client
            if(ret = write(new_socket , message , strlen(message))<0)
            {
                  printf("Sending Error!\n");
            }
            printf("Sent\n");
            //Clear message Var 
            bzero(message,2000);
            //After server has send message to client, Server waiting next message form client
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
                //Means client didn't send anything to server and end connection between server and client
                if(message[0] == 2)
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
