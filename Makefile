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
	rm -f *.o
	rm -f *.html
