#
# To compile, type "make" or make "all"
# To remove files, type "make clean"
#
SERVER_OBJS = server.o request.o helper.o
CLIENT_OBJS = client.o helper.o

CC = gcc
CFLAGS = -g -Werror -Wall -Wno-format-overflow -Wno-restrict

LIBS = -lpthread 

.SUFFIXES: .c .o 

all: server client output.cgi

server: $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o server $(SERVER_OBJS) $(LIBS)

client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o client $(CLIENT_OBJS) $(LIBS)

output.cgi: output.c
	$(CC) $(CFLAGS) -o output.cgi output.c

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-rm -f $(SERVER_OBJS) $(CLIENT_OBJS) server client output.cgi
