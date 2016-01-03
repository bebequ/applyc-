
COMPILER=c++
CFLAG= -O2 -W -DhasPTHREADS -pthread -DNEEDS_UINTPTR_T

DEBUG= -g
LIBS=-lm

INC_DIRS=-I../framework/
LIB_DIRS=-L.

CC=$(COMPILER) $(CFALG) $(DEBUG) $(INC_DIRS) $(DEFINES)
LINK=$(COMPILER) $(LIB_DIRS) $(LIBS)

all: prototype1

clean :
	rm -f *.o prototype1

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

image.o : image.cpp
	$(CC) -c -o image.o image.cpp

lock.o : ../framework/unix/lock.cpp
	$(CC) -c -o lock.o ../framework/unix/lock.cpp

timing.o : ../framework/timing.cpp
	$(CC) -c -o timing.o ../framework/timing.cpp

unitTest.o : ../framework/unitTest.cpp
	$(CC) -c -o unitTest.o ../framework/unitTest.cpp

prototype1 : main.o image.o lock.o timing.o unitTest.o
	$(LINK) main.o image.o lock.o timing.o unitTest.o -o prototype1
