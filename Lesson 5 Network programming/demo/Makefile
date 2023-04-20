#/bin/bash
OBJSS=./src/server.c ./fun/serverfun.c  -I./include 
OBJSC=./src/client.c ./fun/clientfun.c  -I./include 
CC=gcc
all:server client
server:
	$(CC) -o ./bin/server  $(OBJSS) -lsqlite3
client:
	$(CC) -o ./bin/client  $(OBJSC) -lsqlite3
.PHONY:clean
clean:
	rm ./bin/server
	rm ./bin/client
