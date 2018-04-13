#include "common.h"
#include "telegram.h"

#define URL "https://ec2-13-229-209-129.ap-southeast-1.compute.amazonaws.com:8443/"

int main(){
    // telegram_set_webhook(URL, "public.pem");
    // char *me = (char *) malloc(2048);
    // telegram_get_me(me);
    // telegram_send_msg("407156442", 
    // "*Title*\nmessage body\n"
    // "```python\nprint('Code here')\n```\n"
    // "[listen Shonichi](https://www.youtube.com/watch?v=IMx1ojx2fiE)");
    // tcp_server();

    telegram_send_msg("407156442", "sending `test.jpg`");
    telegram_send_act("407156442", "upload_document");
    telegram_send_file("407156442", "htdocs/test.jpg");
    telegram_send_msg("407156442", "Success!");

    return 0;
}