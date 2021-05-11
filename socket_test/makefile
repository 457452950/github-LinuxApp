OBJS = Server3.o 
cc = gcc
#CC = arm-none-linux-gnueabi-gcc
CFLAGS = -g
EXEC = Server3

all:$(EXEC)
$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@  $(OBJS) -lpthread

clean:
	rm -f $(EXEC) *.elf *.gdb *.o
