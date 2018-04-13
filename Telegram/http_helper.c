#include "http_helper.h"

void request_header(struct http_request *request, char *buffer){
    char *temp = (char *) malloc(256);

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%s %s %s\r\n", request->method, request->path, request->version);

    sprintf(temp, "Host: %s\r\n", request->host);
    strcat(buffer, temp);

    strcat(buffer, "Cache-Control: max-age=0\r\n");

    sprintf(temp, "User-Agent: %s\r\n", USER_AGENT);

    if(strlen(request->content_type) > 0){
        if(strcmp(request->content_type, "multipart/form-data") == 0){
            sprintf(temp, "Content-Type: multipart/form-data; boundary="BOUNDARY"\r\n");
        }
        else{
            sprintf(temp, "Content-Type: %s\r\n", request->content_type);
        }
        strcat(buffer, temp);
    }

    strcat(buffer, "Connection: keep-alive\r\n");

    if(request->content_length > 0){
        sprintf(temp, "Content-Length: %d\r\n", request->content_length);
        strcat(buffer, temp);
    }

    strcat(buffer, "\r\n");
    free(temp);
}

void response_header(struct http_response *response, char *buffer){
    char *temp = (char *) malloc(256);

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

    strcat(*buffer, "Content-Type: application/octet-stream\r\n");

    sprintf(temp, "Content-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\n", input_name, filename);
    strcat(*buffer, temp);
    strcat(*buffer, "\r\n");
}

void add_post(char *buffer, char *data, char *field){
    char *temp = (char *) malloc(1024);
    memset(temp, 0, sizeof(temp));

    create_boundary(&temp, data, field);
    strcat(buffer, temp);

    free(temp);
}

void add_file_post(char *buffer, char *filepath, char *field){
    FILE *fp;
    char *temp = (char *) malloc(512);
    memset(temp, 0, sizeof(temp));

    create_file_boundary(&temp, filepath, field);
    strcat(buffer, temp);

    fp = fopen(filepath, "r");
    if(fp != NULL){
        while(!feof(fp)){
            int bufflen = fread(temp, 1, sizeof(temp), fp);
            temp[bufflen] = 0;
            strcat(buffer, temp);
        }
        fclose(fp);
    }

    strcat(buffer, "\r\n");

    free(temp);
}

void end_post(char **buffer){
    strcat(*buffer, "--"BOUNDARY"--");
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