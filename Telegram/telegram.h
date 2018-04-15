#ifndef TELEGRAM_
#define TELEGRAM_

#include "common.h"

#include "openssl/bio.h"

#include "http_helper.h"
#include "http_praser.h"
#include "tcp_client.h"

#define HOST "api.telegram.org"

struct telegram_chat{
    char id[50];
    char msg_id[50];
    char text[4097];
    int date;
    int state;
};

typedef struct telegram_chat Telegram_chat;

int telegram_get_me(char *destination);
int telegram_set_webhook(char *url, char *public_key);
int telegram_send_msg(char *chat_id, char *text);
int telegram_send_act(char *chat_id, char *action);
int telegram_send_file(char *chat_id, char *file_path);

#endif