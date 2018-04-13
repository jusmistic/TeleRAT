#ifndef TELEGRAM_
#define TELEGRAM_

#include "common.h"

#include "openssl/bio.h"

#include "http_helper.h"
#include "http_praser.h"
#include "tcp_client.h"

#define HOST "api.telegram.org"

int telegram_get_me(char *destination);
int telegram_set_webhook(char *url, char *public_key);
int telegram_send_msg(char *chat_id, char *text);

#endif