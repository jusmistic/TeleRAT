#include "tcp_client.h"

int create_connection(BIO **request_bio, char *host){
    SSL *request_ssl;
    SSL_CTX *request_ctx = SSL_CTX_new(SSLv23_client_method());
    if (request_ctx == NULL) {
        printf("errored; unable to load context.\n");
        ERR_print_errors_fp(stderr);
        return -1;
    }

    *request_bio = BIO_new_ssl_connect(request_ctx);
    BIO_get_ssl(*request_bio, &request_ssl);
    SSL_set_mode(request_ssl, SSL_MODE_AUTO_RETRY);

    BIO_set_conn_hostname(*request_bio, host);

    if(BIO_do_connect(*request_bio) <= 0){
        printf("Error connection\n");
        return -1;
    }

    return 1;
}

int create_request(char *buffer, BIO **request_bio, struct http_request *request_struct){
    SSL *request_ssl;
    strcpy(request_struct->version, "HTTP/1.1");

    request_header(request_struct, buffer);
    
    char *host = (char *) malloc(100);
    sprintf(host, "%s:443", request_struct->host);
    create_connection(request_bio, host);

    free(host);
}

int write_request(BIO **request_bio, char *request, unsigned int len){
    int res;
    if((res = BIO_write(*request_bio, request, len)) <= 0){
        printf("errored; unable to write. with error %d\n", res);
        BIO_free_all(*request_bio);
        
        ERR_print_errors_fp(stderr);
        return -1;
    }
}

int get_response(BIO **request_bio, char *response){
    int res;
    char read_buffer[BUFFER_SIZE];
    while(1){
        res = BIO_read(*request_bio, read_buffer, BUFFER_SIZE);
        if(res < 0){
            if(!BIO_should_retry(*request_bio)){
                printf("Error: read failed");
                ERR_print_errors_fp(stderr);
                return -1;
            }
        }
        else{
            read_buffer[res] = 0;
            strcpy(response, read_buffer);
            return 1;
        }
    }
}