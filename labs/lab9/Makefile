CC = gcc
DEPS = uwecSocket.h

%.o: %.cc $(DEPS)
	$(CC) -c -o -fopenmp $@ $< $(CFLAGS)

node: uwecSocket.c node.c
	$(CC) uwecSocket.c node.c -o node

head: uwecSocket.c head.c
	$(CC) uwecSocket.c head.c -o head -fopenmp

clean:
	rm node
	rm head

