cc = gcc
cflags = -g
lib_path = Telegram/includes/

all: helper tcp_server.o telegram_server tcp_server.a

helper:
	cd Telegram && make all && cd ..

tcp_server.o: tcp_server.c
	$(cc) $(cflags) -c $^ -o $@

tcp_server.a: tcp_server.o $(lib_path)telegram.o $(lib_path)http_helper.o \
		$(lib_path)http_praser.o $(lib_path)json_helper.o $(lib_path)tcp_client.o
	ar rcs $@ $^

telegram_server: telegram_server.c tcp_server.a
	$(cc) $(cflags) $^ -o $@ -lssl -lcrypto

clean:
	rm -f *.a *.o
	cd Telegram && make clean && cd ..