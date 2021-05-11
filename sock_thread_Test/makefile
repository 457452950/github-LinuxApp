PP = g++
TARGET = Client Server _freecplus.o
OBJS = Client.o Server.o

all : $(TARGET)


Server:Server.cpp 
	$(PP) -g -o $@ Server.cpp _freecplus.cpp  -lpthread


Client:Client.cpp 
	$(PP) -g -o $@ Client.cpp _freecplus.cpp  -lpthread	


clean :
	rm -f *.o $(TARGET)