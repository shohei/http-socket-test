PROGRAM = main
OBJS = main.o openurl.o
CFLAGS= -Wall -O2
CC = gcc $(CFLAGS)

.SUFFIXES: .o .c

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

.c.o: 
	$(CC) -c $<

.PHONY:
	clean

clean:
	rm *.o
	rm *.html
