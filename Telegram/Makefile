cc = gcc
cflags = -g
output_path = includes/

all: http_helper.o http_praser.o json_helper.o tcp_client.o telegram.o \
	 telegram.a main

http_helper.o: http_helper.c
	$(cc) $(cflags) -c $^ -o $(output_path)$@

http_praser.o: http_praser.c
	$(cc) $(cflags) -c $^ -o $(output_path)$@

json_helper.o: json_helper.c
	$(cc) $(cflags) -c $^ -o $(output_path)$@

tcp_client.o: tcp_client.c
	$(cc) $(cflags) -c $^ -o $(output_path)$@

telegram.o: telegram.c
	$(cc) $(cflags) -c $^ -o $(output_path)$@

telegram.a: $(output_path)telegram.o $(output_path)http_helper.o \
			$(output_path)http_praser.o $(output_path)tcp_client.o
	ar rcs $@ $^

main: main.c telegram.a
	$(cc) $(cflags) $^ -o $@ -lssl -lcrypto

clean:
	rm -f $(output_path)*.o $(output_path)*.a
	rm -f *.a