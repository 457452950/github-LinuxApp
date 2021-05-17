OBJS = Server3.o Server2.o Server.o Client3.o Client.o
cc = gcc

CFLAGS = -g
EXEC = Server3 Server2 Server Client3 Client

all:$(EXEC)

Server3:Server3.o
	$(CC) $(CFLAGS) -o $@  Server3.o -lpthread


Server2:Server2.o
	$(CC) $(CFLAGS) -o $@  Server2.o -lpthread


Server:Server.o
	$(CC) $(CFLAGS) -o $@  Server.o -lpthread


Client3:Client3.o
	$(CC) $(CFLAGS) -o $@  Client3.o -lpthread

Client:Client.o
	$(CC) $(CFLAGS) -o $@  Client.o -lpthread


clean:
	rm -f $(EXEC) *.elf *.gdb *.o
