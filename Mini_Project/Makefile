all: server client
.PHONY: clean

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client

clean:
	rm client server out