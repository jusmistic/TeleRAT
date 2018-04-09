#include "telegram.h"

int telegram_set_webhook(char *url, char *public_key, BIO **request_bio){
    FILE *fp;
    char *response = (char *) malloc(2048);
    char *buffer = (char *) malloc(512);

    struct http_request request_struct = {
        .method = "POST",
        .path = "/bot591458604:AAHOF6mhG6ft9Zyvr2bCciFWKiXsuSJmD9Q/setWebhook",
        .host = "api.telegram.org",
        .content_type = "multipart/form-data",
    };

    send_request(request_bio, &request_struct);

    create_boundary(&buffer, url, "url");
    write_request(request_bio, buffer, strlen(buffer));

    create_boundary(&buffer, public_key, "certificate");
    write_request(request_bio, buffer, strlen(buffer));

    // fp = fopen(public_key, "r");
    // if(fp != NULL){
    //     int bufflen = 0;
    //     while(!feof(fp)){
    //         bufflen = fread(buffer, 1, sizeof(buffer), fp);
    //         buffer[bufflen] = 0;
    //         write_request(request_bio, buffer, bufflen);
    //     }
    //     fclose(fp);
    // }

    // sprintf(buffer, "\r\n");
    // write_request(request_bio, buffer, strlen(buffer));

    sprintf(buffer, "--"BOUNDARY"--\r\n");
    write_request(request_bio, buffer, strlen(buffer));
    get_response(request_bio, response);

    printf("Response body =>\n%s\n", response);

    return 1;
}