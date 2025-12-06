# IDIR = ./include
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror -g3 -O0

day1: day1.o 
	$(CC) $(CFLAGS) -o day1 day1.o 

day1b: day1b.o
	$(CC) $(CFLAGS) -o day1b day1b.o

run: day1b
	./day1 ./input.txt
	./day1b ./input.txt
	
clean:
	rm -f day1 *.o
