#include "include/common.h"
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h>

#define OP_START '\\x02'
#define OP_STOP "\x03"

void *connect_handle(void * temp_struct);
struct sendto_function {
    int *client_soc;
    char *ip_client[50];
}sendto_function;
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c, *new_sock;
    struct sockaddr_in server , client;
    char copy_message;
    int potnumber_server;

    potnumber_server = atoi(argv[1]); 
    if (2 != argc) {

        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);

    } 
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
    server.sin_port = htons(potnumber_server);
     
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
    struct sendto_function send_to_function;

    while ( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        //accept connection form client complete
        pthread_t server_serv;
        *send_to_function.ip_client = inet_ntoa(client.sin_addr);
        send_to_function.client_soc = malloc(sizeof *send_to_function.client_soc);
        *send_to_function.client_soc = client_sock;
        if( pthread_create( &server_serv , NULL ,  connect_handle , (void*) &send_to_function) < 0)
        {
            perror("could not create thread");
            return 1;
        }
    } 
    if (client_sock<0)
    {
        printf("accept failed");
        return 1;
    }
     
    return 0;
}


void *connect_handle(void * temp_struct){
    struct sendto_function socket_struct = *(struct sendto_function *) temp_struct;
    printf("Connection accepted ");
    int new_socket = *socket_struct.client_soc;
    char message[2000]="", ipclient[100];
    int ret;
    char buf[256];
    strcpy(ipclient, *socket_struct.ip_client);
    printf("Client socket: %d\nIP: %s\n", new_socket, ipclient);
    while(1) {
		memset(buf, 0, 256);

		//Reply to the client
		    //Server send message to client
		    bzero(message,2000);
		    // scanf(" %[^\n]",message);
		    // printf("%s\n",message);
		    //If write(new_socket , message , strlen(message) < 0 it means Server didn't send anything to client
		    if(ret = write(new_socket , message , strlen(message))<0)
		    {
		          printf("Sending Error!\n");
		    }
		    // printf("Sent\n");
		    //Clear message Var 
		    bzero(message,2000);
		    //After server has send message to client, Server waiting next message form client
		    // printf("Server Read\n");
		    while(1)
		    {
		        bzero(message,2000);
		        // printf("Start Sending\n");
				if(read(new_socket, message, 200) < 0)
		        {
		            printf("Recv Error!\n");                
		        }
                if(strcmp(message,OP_STOP) == 0)
		        {
		            // printf("Exit..");
                    break;
		        }    
		        printf("%s", message);
		        //Means client didn't send anything to server and end connection between server and client
          
		    }
		    // printf("Stop Recieve...\n");

	}
}