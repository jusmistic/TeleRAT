#ifndef TCP_SERVER_
#define TCP_SERVER_

#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"
#include "openssl.h"

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