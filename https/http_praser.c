#include "http_praser.h"

void http_split_header(char *http_response){
    char *http_data;
    char *temp = NULL;

    strcpy(http_data, http_response);

    temp = strtok(http_data, "\r\n");
    while(temp != NULL){
        printf("\n%s\n", temp);
        temp = strtok(NULL, "\r\n");
    }
}

void http_request_path(char *http_request, char *path){
    /* Get request path */
    if(strncmp(http_request, "GET ", 4) == 0){
        char temp[256];
        int index = 0;

        for(int i = 4; http_request[i] != ' '; i++){
            temp[index++] = http_request[i];
        }
        strcpy(path, temp);
    }
}

int http_content_length(char *http_response){
    
}

/* Return length of http_response body */
int http_reponse_body(char *http_response, char *body){

}