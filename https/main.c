#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/bio.h"

#include "telegram.h"

#define URL "https://ec2-18-219-162-217.us-east-2.compute.amazonaws.com:8443/"

int main(){
    BIO *request_bio;
    telegram_set_webhook(URL, "public.pem", &request_bio);
    return 0;
}