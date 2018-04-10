#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/bio.h"

#include "telegram.h"

#define URL "https://ec2-18-219-162-217.us-east-2.compute.amazonaws.com:8443"

int main(){
    // telegram_set_webhook(URL, "public.pem");
    char *me = (char *) malloc(2048);
    telegram_get_me(me);
    telegram_send_msg("407156442", "Test Telegram sendMessage Method");
    return 0;
}