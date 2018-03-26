#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;
    char buf[2000];
    char text[200000]="";
    char tmp[250];
    scanf("%[^\n]",tmp);

    if ((fp = popen(tmp,"r")) != 0)
    {
        //popen execute command
        printf("popen: Read stream output and save to text\n");

        //fgets output untill done
        while (fgets(buf, 2000, fp) != 0) {
            // fputs(buf, stdout); //Use when you want to print string
            strcat(text,buf); //include stream to text
        }
        //print exec out
        printf("%s",text);
    }
    else if(fp == NULL){
        printf("shell execute error");
        exit(1);
    }
    //close command pipe
    fclose(fp);
}
