#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h> //atoi
struct cmdinfo{
    char nowPath[1024];
    char pName[250];

    char moveTo[1024];
    char cmd[5000];
} path;

//Get Now file location
struct cmdinfo getnowPath(struct cmdinfo pathGet){
    if (getcwd(pathGet.nowPath, sizeof(pathGet.nowPath)) == NULL)
       perror("getcwd() error");
    return pathGet;
}


int main(){
    path = getnowPath(path);
    FILE *fp;
    sprintf(path.nowPath,"%s/test.txt",path.nowPath);
    fp = fopen(path.nowPath,"w");
    fprintf(fp, "This is testing wasd fprintf...\n");
    // fputs("This is testing for fputs...\n", fp);
    fclose(fp);

    return 0;
}