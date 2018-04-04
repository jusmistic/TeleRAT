#ifndef HTTP_PRASER_
#define HTTP_PRASER_

#include <stdio.h>
#include <string.h>

void http_split_header(char http_response[]);
void http_request_path(char *http_request, char *path);
int http_content_length(char *http_response);
int http_reponse_body(char *http_response, char *body);

#endif