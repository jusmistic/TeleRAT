#include "http_helper.h"

void request_header(struct http_request *request, char *buffer){
    // *buffer = (char *) malloc(1024);
    char *temp = (char *) malloc(256);

    // memset(*buffer, 0, sizeof(*buffer));
    sprintf(buffer, "%s %s %s\r\n", request->method, request->path, request->version);

    sprintf(temp, "Host: %s\r\n", request->host);
    strcat(buffer, temp);

    strcat(buffer, "Connection: keep-alive\r\n");

    sprintf(temp, "User-Agent: %s\r\n", USER_AGENT);
    strcat(buffer, temp);

    if(strlen(request->content_type) > 0){
        if(strcmp(request->content_type, "multipart/form-data") == 0){
            sprintf(temp, "Content-Type: %s; boundary=%s\r\n", request->content_type, BOUNDARY);
        }
        else{
            sprintf(temp, "Content-Type: %s", request->content_type);
        }
        strcat(buffer, temp);
    }

    strcat(buffer, "\r\n");
    free(temp);
}

void response_header(struct http_response *response, char *buffer){
    // *buffer = (char *) malloc(1024);
    char *temp = (char *) malloc(256);

    // memset(*buffer, 0, sizeof(*buffer));
    sprintf(buffer, "%s %d %s\r\n", response->version, response->status_code, response->status);

    sprintf(temp, "Server : "SERVER"\r\n");
    strcat(buffer, temp);

    sprintf(temp, "Content-Type: %s; charset=%s\r\n", response->content_type, response->charset);
    strcat(buffer, temp);

    sprintf(temp, "Content-Length: %d\r\n", response->content_length);
    strcat(buffer, temp);

    strcat(buffer, "\r\n");

    free(temp);
}

void create_boundary(char **buffer, char *data, char *input_name){
    // *buffer = (char *) malloc(2048);
    char *temp = (char *) malloc(256);

    memset(*buffer, 0, sizeof(*buffer));

    sprintf(temp, "--"BOUNDARY"\r\n");
    strcat(*buffer, temp);

    sprintf(temp, "Content-Disposition: form-data; name=\"%s\"\r\n", input_name);
    strcat(*buffer, temp);
    strcat(*buffer, "\r\n");

    strcat(*buffer, data);
    strcat(*buffer, "\r\n");
}

void create_file_boundary(char **buffer, char *file_path, char *input_name){
    // *buffer = (char *) malloc(2048);
    char *temp = (char *) malloc(256);

    memset(*buffer, 0, sizeof(*buffer));

    sprintf(temp, "--"BOUNDARY"\r\n");
    strcat(*buffer, temp);

    int j = 0;
    char filename[100];
    for(int i = strlen(file_path) - 1; file_path[i] != '/' && i >= 0; i--){
        temp[j++] = file_path[i];
    }
    temp[j] = '\0';
    reverse_str(filename, temp);

    sprintf(temp, "Content-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\n", input_name, filename);
    strcat(*buffer, temp);
    strcat(*buffer, "\r\n");
}

void reverse_str(char *destination, char *source){
    char temp[100];
    int j = strlen(source) - 1, i = 0;

    for(i, j; j >= 0; j--, i++){
        temp[i] = source[j];
    }
    temp[i] = '\0';

    strcpy(destination, temp);
}