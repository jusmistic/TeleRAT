cc = gcc
cflags = -g
lib_path = Telegram/includes/

all: helper tcp_server.o tcp_server.a server-d client-d include/util.o set_webhook

helper:
	cd Telegram && make all && cd ..

tcp_server.o: tcp_server.c
	$(cc) $(cflags) -c $^ -o $@

tcp_server.a: tcp_server.o $(lib_path)telegram.o $(lib_path)http_helper.o \
		$(lib_path)http_praser.o $(lib_path)json_helper.o $(lib_path)tcp_client.o
	ar rcs $@ $^

include/util.o: include/util.c
	$(cc) $(cflags) -c $^ -o $@

server-d: server-d.c tcp_server.a include/util.o
	$(cc) $(cflags) $^ -o $@ -lssl -lcrypto -lpthread

client-d: client-d.c include/util.o Telegram/telegram.a
	$(cc) $(cflags) $^ -o $@ -lssl -lcrypto

set_webhook: set_webhook.c Telegram/telegram.a
	$(cc) $(cflags) $^ -o $@ -lssl -lcrypto

clean:
	rm -f *.a *.o
	rm -f server-d client-d set_webhook
	cd Telegram && make clean && cd ..