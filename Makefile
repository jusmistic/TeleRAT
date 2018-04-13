cc = gcc
cflags = -g
lib_path = Telegram/

all: helper.a tcp_server.o telegram_server

helper.a:
	cd Telegram && make all && cd ..

tcp_server.o: tcp_server.c
	$(cc) $(cflags) -c $^ -o $@

telegram_server: telegram_server.c tcp_server.o $(lib_path)helper.a
	$(cc) $(cflags) $^ -o $@ -lssl -lcrypto

clean:
	rm -f tcp_server.o telegram_server