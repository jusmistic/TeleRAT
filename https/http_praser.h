#ifndef HTTP_PRASER_
#define HTTP_PRASER_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_helper.h"

void prase_request(struct http_request *request, char *http_request_str);
void prase_response(struct http_response *response, char *http_response_str);
void get_body(char *destination, char *http_data);
int search(char *str, char *target);

#endif