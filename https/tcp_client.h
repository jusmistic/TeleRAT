#ifndef TCP_CLIENT_
#define TCP_CLIENT_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

// openSSL
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/bio.h"

#include "http_helper.h"
#include "http_praser.h"

#define BUFFER_SIZE 20480

int create_connection(BIO **request_bio, char *host);
int create_request(char *buffer, BIO **request_bio, struct http_request *request_struct);
int write_request(BIO **request_bio, char *request, unsigned int len);
int get_response(BIO **request_bio, char *response);

#endif