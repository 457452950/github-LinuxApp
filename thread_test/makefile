PP = g++
CC = gcc
EXEC = threadTest
OBJS = threadTest.o
FLAG = -g -o

all:$(EXEC)

$(EXEC):$(OBJS)
	$(PP) $(FLAG) $@ $(OBJS) -lpthread

clean:
	rm -f $(OBJS) $(EXEC)
 
