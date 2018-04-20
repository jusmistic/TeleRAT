#ifndef UTIL_HEADER
#define UTIL_HEADER

#include "common.h"

struct cmd_struct{
    char nowPath[1024];
    char cmd[10000];
    char moveTo[2048];
};

void i_am_root();
void getpName(char *pName);
void getNowPath(char *nowPath);
void exeCMD(char *cmd);
void initSetiing(char *path,char *pName,char *ip,char *port);
void move(char *path, char *pName);
void boom(char *path,char *pName);
char *help();
void getHostname(char *hostname);
#endif 