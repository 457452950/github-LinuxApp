PP=g++
CC=gcc
OBJS=myThreadPool.o
Target=myThreadPool 

ALL:$(Target)

$(Target):myThreadPool.cpp
	$(PP) -o $(Target) myThreadPool.cpp -lpthread


clean:
	rm -f $(Target) $(OBJS)





# gcc -o myThreadPool myThreadPool.c -lpthread