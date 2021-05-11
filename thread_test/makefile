PP = g++
CC = gcc
EXEC = threadTest thread
OBJS = threadTest.o thread.o
FLAG = -g -o

all:$(EXEC)

threadTest:threadTest.o
	$(PP) $(FLAG) $@ threadTest.o -lpthread


thread:thread.o
	$(PP) $(FLAG) $@ threadTest.o -lpthread



clean:
	rm -f $(OBJS) $(EXEC)
 
