CC = gcc
CFLAGS = -Wall

all: main

main: main.o connection.o interface.o
	$(CC) $(CFLAGS) -o main main.o connection.o interface.o

main.o: main.c connection.h interface.h
	$(CC) $(CFLAGS) -c main.c


connection.o: connection.c connection.h
	$(CC) $(CFLAGS) -c connection.c

clean:
	rm -f *.o main
