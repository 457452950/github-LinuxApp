OBJS = copy_file.o
CC = gcc
EXEC = test

all:$(EXEC)

$(EXEC):$(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(EXEC) *.o
	