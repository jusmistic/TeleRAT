#include "Telegram/telegram.h"

int main(int argc , char *argv[]){
    telegram_set_webhook(argv[1], "public.pem");
    return 0;
}