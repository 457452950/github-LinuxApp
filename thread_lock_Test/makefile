CC = gcc
PP = g++
OBJS = test.o epoll_test.o
FLAGS = -g -o 
TAGETS = test epoll_test

all : test epoll_test

test : test.cpp
	$(PP) $(FLAGS) $@ test.cpp -lpthread



epoll_test : epoll_test.cpp
	$(PP) $(FLAGS) $@ epoll_test.cpp -lpthread

clean :
	rm -f *.o $(TAGETS)


