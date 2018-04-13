#ifndef TCP_SERVER_
#define TCP_SERVER_

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
#include "telegram.h"
#include "json_helper.h"

#define BUFFER_SIZE 20480

SSL_CTX *create_context();
void init_openssl();
void cleanup_openssl();
void configure_context(SSL_CTX *ctx);
int tcp_server();

#endif