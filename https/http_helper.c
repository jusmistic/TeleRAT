#include "http_helper.h"

void request_header(struct http_request *request, char **buffer){
    *buffer = (char *) malloc(1024);
    char *temp = (char *) malloc(256);
    sprintf(*buffer, "%s %s %s\r\n", request->method, request->path, request->version);

    sprintf(temp, "HOST: %s\r\n", request->host);
    strcat(*buffer, temp);

    sprintf(temp, "User-Agent: %s\r\n", USER_AGENT);
    strcat(*buffer, temp);

    if(strlen(request->content_type) > 0){
        if(strcmp(request->content_type, "multipart/form-data") == 0){
            sprintf(temp, "Content-Type: %s;boundary=%s\r\n", request->content_type, BOUNDARY);
        }
        else{
            sprintf(temp, "Content-Type: %s", request->content_type);
        }
        strcat(*buffer, temp);
    }

    strcat(*buffer, "\r\n");
    free(temp);
}

void response_header(struct http_response *response, char **buffer){
    *buffer = (char *) malloc(1024);
    char *temp = (char *) malloc(256);
    sprintf(*buffer, "%s %d %s\r\n", response->version, response->status_code, response->status);

    sprintf(temp, "Server : "SERVER"\r\n");
    strcat(*buffer, temp);

    sprintf(temp, "Content-Type: %s; charset=%s\r\n", response->content_type, response->charset);
    strcat(*buffer, temp);

    sprintf(temp, "Content-Length: %d\r\n", response->content_length);
    strcat(*buffer, temp);

    strcat(*buffer, "\r\n");

    free(temp);
}