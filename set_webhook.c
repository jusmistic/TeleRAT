#include "Telegram/telegram.h"
#define URL "https://ec2-13-229-209-129.ap-southeast-1.compute.amazonaws.com:8443"

int main(){
    telegram_set_webhook(URL, "public.pem");
    return 0;
}