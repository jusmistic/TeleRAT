#include "telegram.h"

int telegram_set_webhook(char *url, char *public_key, BIO **request_bio){
    FILE *fp;
    char *response = (char *) malloc(2048);
    char *buffer = (char *) malloc(20480);
    char *temp = (char *) malloc(20480);

    struct http_request request_struct = {
        .method = "POST",
        .path = "/bot591458604:AAHOF6mhG6ft9Zyvr2bCciFWKiXsuSJmD9Q/setWebhook",
        .host = "api.telegram.org",
        .content_type = "multipart/form-data",
    };

    memset(buffer, 0, sizeof(buffer));

    create_boundary(&temp, url, "url");
    strcat(buffer, temp);

    create_file_boundary(&temp, public_key, "certificate");
    strcat(buffer, temp);

    memset(temp, 0, sizeof(temp));
    fp = fopen(public_key, "r");
    if(fp != NULL){
        while(!feof(fp)){
            int bufflen = fread(temp, 1, sizeof(temp), fp);
            temp[bufflen] = 0;
            strcat(buffer, temp);
        }
        fclose(fp);
    }

    strcat(buffer, "\r\n");
    strcat(buffer, "--"BOUNDARY"--");

    request_struct.content_length = strlen(buffer);

    create_request(temp, request_bio, &request_struct);
    strcat(temp, buffer);
    strcpy(buffer, temp);

    write_request(request_bio, buffer, strlen(buffer));
    get_response(request_bio, response);

    // free(temp);

    printf("\nResponse =>\n%s\n", response);

    return 1;
}