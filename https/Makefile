cc = gcc
cflags = -g

all: http_helper.o http_praser.o json_helper.o tcp_client.o telegram.o telegram.a

http_helper.o: http_helper.c
	$(cc) $(cflags) -c $^ -o $@

http_praser.o: http_praser.c
	$(cc) $(cflags) -c $^ -o $@

json_helper.o: json_helper.c
	$(cc) $(cflags) -c $^ -o $@

tcp_client.o: tcp_client.c
	$(cc) $(cflags) -c $^ -o $@

telegram.o: telegram.c
	$(cc) $(cflags) -c $^ -o $@

telegram.a: http_helper.o http_praser.o json_helper.o tcp_client.o telegram.o
	ar rcs $@ $^


clean:
	rm -f *.o *.a