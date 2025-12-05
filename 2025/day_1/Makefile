# IDIR = ./include
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror -g3 -O0

day1: day1.o 
	$(CC) $(CFLAGS) -o day1 day1.o 

run: day1
	./day1 ./input.txt
	
clean:
	rm -f day1 *.o
