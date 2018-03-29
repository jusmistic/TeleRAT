#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h> //atoi
struct paths{
    char nowpath[1024];
    char pName[250];

    char moveTo[1024];
    char cmd[5000];
};
struct paths getpName(struct paths pName){
    int len=0;
    len = strlen(pName.pName);
    //parse ./move -> /move
    strncpy(pName.pName,pName.pName+1,len-1);
    //add null byte for stop string
    pName.pName[len-1] ='\0';
    return pName;
}
struct paths getNowPath(struct paths pathGet){
    if (getcwd(pathGet.nowpath, sizeof(pathGet.nowpath)) == NULL)
       perror("getcwd() error");
    return pathGet;
}
struct paths move(struct paths pathMove){
    //Get now program location
    pathMove = getNowPath(pathMove);
    pathMove = getpName(pathMove);
    //parse path to cmd
    sprintf(pathMove.cmd,"mv %s%s %s%s",pathMove.nowpath,pathMove.pName,pathMove.moveTo,pathMove.pName);
    return pathMove;
}

int main(int argc , char *argv[]){
    char buf[250];

    struct paths path;
    strcpy(path.pName,argv[0]);
    strcpy(path.moveTo,argv[1]);


    path = move(path);
    FILE *fp = popen(path.cmd, "r");
    
    while (fgets(buf, 200, fp))
    {
        printf("%s:",buf);
        bzero(path.cmd,200);
        bzero(buf,200); 
    }


    return 0;
}