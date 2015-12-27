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
image.o: image.cpp
	$(CC) -c -o image.o image.cpp

testapplication: image.o
	echo "compile complete!"
