#ifndef UTIL_HEADER
#define UTIL_HEADER

#include "common.h"

struct cmd_struct{
    char nowPath[1024];
    char cmd[10000];
    char moveTo[2048];
} cmd;

void i_am_root();
void getpName(char *pName);
void getNowPath(char *nowPath);
void exeCMD(char *cmd);
void move(char *path, char *pName);
void boom(char *path,char *pName);
void serviceSetting(char *pName);
void getHostname(char *hostname);
#endif 