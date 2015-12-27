COMPILER=g++
CFLAGS= -O2 -W
DEBUG= -g
LIBS= -lm

INCDIRS= -I../src
LIBDIRS= -L../src

CC=$(COMPILER) $(CFLAGS) $(DEBUG) $(INCDIRS) $(DEF)
LINK=$(CC) $(LIBDIRS) $(LIBS)

SRC_PATH=../src

all: testapplication

clean:
	rm -f *.o testapplication

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

image.o: image.cpp
	$(CC) -c -o image.o image.cpp

thumbnail.o : thumbnail.cpp
	$(CC) -c -o thumbnail.o thumbnail.cpp

testapplication: main.o image.o thumbnail.o
	$(LINK) main.o image.o thumbnail.o -o testapplication 
