#ifndef TELEGRAM_
#define TELEGRAM_

#include "common.h"

#include "openssl/bio.h"

#include "http_helper.h"
#include "http_praser.h"
#include "tcp_client.h"

#define HOST "api.telegram.org"
#define MSG_ID_LENGTH 50
#define ID_LENGTH 50
#define TEXT_LENGTH 4097

struct telegram_chat{
    char id[ID_LENGTH];
    char msg_id[MSG_ID_LENGTH];
    char text[TEXT_LENGTH];
    int date;
    int state;
};

typedef struct telegram_chat Telegram_chat;

int telegram_init(struct telegram_chat *chat);
int telegram_check(struct telegram_chat *chat);
int telegram_check(struct telegram_chat *chat);
int telegram_mark_send(struct telegram_chat *chat);
int telegram_mark_new(struct telegram_chat *chat);
int telegram_get_me(char *destination);
int telegram_set_webhook(char *url, char *public_key);
int telegram_send_msg(char *chat_id, char *text);
int telegram_send_act(char *chat_id, char *action);
int telegram_send_file(char *chat_id, char *file_path);

#endif