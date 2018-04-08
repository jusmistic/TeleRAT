#ifndef HTTP_PRASER_
#define HTTP_PRASER_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct http_request{
    char method[10];
    char path[256];
    char version[10];
    char host[256];
    char content_type[20];
    unsigned int content_length;
};

struct http_response{
    char version[10];
    int status_code;
    char status[100];
    char content_type[20];
    char charset[10];
    unsigned int content_length;
};

void prase_request(struct http_request *request, char *http_request_str);
void prase_response(struct http_response *response, char *http_response_str);
void get_body(char *destination, char *http_data);
int search(char *str, char *target);

#endif