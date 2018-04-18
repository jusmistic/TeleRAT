#ifndef TCP_SERVER_
#define TCP_SERVER_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "Telegram/common.h"
#include "Telegram/openssl.h"

#include "Telegram/http_helper.h"
#include "Telegram/http_praser.h"
#include "Telegram/telegram.h"
#include "Telegram/json_helper.h"

#define BUFFER_SIZE 20480

SSL_CTX *create_context();
void init_openssl();
void cleanup_openssl();
void configure_context(SSL_CTX *ctx);
int tcp_server();

#endif