CC = gcc
CFLAGS = -Wall

all: main

main: main.o auth.o schedule.o data.o utils.o connection.o
	$(CC) $(CFLAGS) -o main main.o auth.o schedule.o data.o utils.o connection.o

main.o: main.c auth.h schedule.h data.h utils.h connection.h
	$(CC) $(CFLAGS) -c main.c

auth.o: auth.c auth.h
	$(CC) $(CFLAGS) -c auth.c

schedule.o: schedule.c schedule.h data.h
	$(CC) $(CFLAGS) -c schedule.c

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

connection.o: connection.c connection.h auth.h schedule.h data.h
	$(CC) $(CFLAGS) -c connection.c

clean:
	rm -f *.o main
