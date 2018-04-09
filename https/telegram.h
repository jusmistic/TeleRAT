#ifndef TELEGRAM_
#define TELEGRAM_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/bio.h"

#include "http_helper.h"
#include "http_praser.h"
#include "tcp_client.h"

#define HOST "api.telegram.org"

int telegram_set_webhook(char *url, char *public_key, BIO **request_bio);
// int telegram_get_me(char *destination);
// int telegram_send_msg(char *chat_id, char *text);

#endif