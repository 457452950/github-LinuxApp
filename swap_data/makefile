OBJS = swap_data.o test.o
#cc = gcc
CC = arm-none-linux-gnueabi-gcc
CFLAGS = -g
EXEC = test

all:$(EXEC)
$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(EXEC) *.elf *.gdb *.o
