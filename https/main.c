#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/bio.h"

#include "telegram.h"

#define URL "https://ec2-13-229-209-129.ap-southeast-1.compute.amazonaws.com:8443/"

int main(){
    telegram_set_webhook(URL, "public.pem");
    // char *me = (char *) malloc(2048);
    // telegram_get_me(me);
    // telegram_send_msg("407156442", 
    // "*Title*\nmessage body\n"
    // "```python\nprint('Code here')\n```\n"
    // "[listen Shonichi](https://www.youtube.com/watch?v=IMx1ojx2fiE)");
    return 0;
}