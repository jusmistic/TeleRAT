#ifndef TELEGRAM_
#define TELEGRAM_

#define HOST "api.telegram.org"

int telegram_set_webhook(char *url, char *public_key);
int telegram_get_me(char *destination);
int telegram_send_msg(char *chat_id, char *text);

#endif