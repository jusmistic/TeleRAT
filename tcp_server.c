#include "tcp_server.h"

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void init_openssl(){
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
    SSL_library_init();
}

void cleanup_openssl()
{
    EVP_cleanup();
}

/* Config SSL context */
void configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "public.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "private.pem", SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

/* Get request and response HTTPS */
int response(int client_socket, Telegram_chat *chat, SSL **ssl){
    unsigned int bufflen, readlen;
    char buffer[BUFFER_SIZE], readBuffer[BUFFER_SIZE];
    char *temp = (char *) malloc(10240);

    FILE *file;
    file = fopen("htdocs/index.html", "r");

    /* Buffer IO Init*/
    BIO *out;
    BIO *ssl_bio;
    ssl_bio = BIO_new(BIO_f_ssl());
    out = BIO_new(BIO_s_connect());

    BIO_set_ssl(ssl_bio, *ssl, BIO_CLOSE);
    BIO_set_nbio(out, 1);

    out = BIO_push(ssl_bio, out);

    memset(readBuffer, 0, sizeof(readBuffer));
    memset(temp, 0, sizeof(temp));

    /* Read HTTP request Header */
    printf("[HTTP Request]\n");

    struct http_request request;
    readlen = BIO_read(ssl_bio, readBuffer, sizeof(readBuffer));
    if(readlen > 0){
        prase_request(&request, readBuffer);
        printf("%s", readBuffer);
    }
    else{
        return -1;
    }

    /* Read request body*/
    unsigned int temp_length = request.content_length;
    if(request.content_length > 0){
        while(temp_length > 0){
            readlen = BIO_read(ssl_bio, readBuffer, sizeof(readBuffer));
            temp_length -= readlen;
            strcat(temp, readBuffer);
            // printf("%s", readBuffer);
        }
    }

    printf("%s", temp);
    get_telegram_chat(chat, temp);

    if(chat->date - (int)time(NULL) > 5){
        printf("This message id (%s) older than 5 second\n", chat->msg_id);
        return -1;
    }

    printf("\n\nText => %s\n", chat->text);
    free(temp);
    bzero(readBuffer, sizeof(readBuffer));

    char *http_header = (char *) malloc(256);
    struct http_response response = {
        .version = "HTTP/1.1",
        .status_code = 200,
        .status = "OK",
        .content_type = "text/html",
        .charset = "utf-8"
    };

    if(file){
        response.content_length = 0;

        // Content-Length
        while((bufflen = fread(buffer, 1, BUFFER_SIZE, file)) > 0){
            response.content_length += bufflen;
        }

        response_header(&response, http_header);

        strcpy(buffer, http_header);

        // printf("[HTTP Response]\n%s", buffer);
        BIO_write(out, http_header, strlen(http_header));
        rewind(file);

        if(file != NULL){
            while(!feof(file)){
                bufflen = fread(buffer, 1, BUFFER_SIZE, file);
                buffer[bufflen] = 0;
                BIO_write(out, &buffer, bufflen);
            }
            fclose(file);
        }

        return 1;
    }
}

int tcp_server(Telegram_chat *chat){
    SSL *ssl;
    SSL_CTX *ctx;
    init_openssl();
    ctx = create_context();
    configure_context(ctx);

    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        perror("Unable to create socket");
        return -1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8443);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0){
        perror("Unable to bind");
        return -1;
    }

    if(listen(server_socket, 5) < 0){
        perror("Unable to listen");
        return -1;
    }

    while(1){
        struct sockaddr_in client_address;
        unsigned int len = sizeof(client_address);

        int client_socket = accept(server_socket, (struct sockaddr *) &client_address, &len);
        if (client_socket < 0) {
            perror("Unable to accept");
            return -1;
        }

        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client_socket);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        }
        else {
            response(client_socket, chat, &ssl);
        }
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }

    SSL_CTX_free(ctx);
    close(server_socket);
    cleanup_openssl();
}