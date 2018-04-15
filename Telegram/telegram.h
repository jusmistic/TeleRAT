#ifndef TELEGRAM_
#define TELEGRAM_

#include "common.h"

#include "openssl/bio.h"

#include "http_helper.h"
#include "http_praser.h"
#include "tcp_client.h"

#define HOST "api.telegram.org"

struct telegram_chat{
    char id[15];
    char text[256];
};

typedef struct telegram_chat Telegram_chat;

int telegram_get_me(char *destination);
int telegram_set_webhook(char *url, char *public_key);
int telegram_send_msg(char *chat_id, char *text);
int telegram_send_act(char *chat_id, char *action);
int telegram_send_file(char *chat_id, char *file_path);

#endif