CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -O0

day5: day5.o 
	$(CC) $(CFLAGS) -o day5 day5.o 

day5b: day5b.o
	$(CC) $(CFLAGS) -o day5b day5b.o

run: day5
	./day5 ./sample.txt
	./day5 ./input.txt
	./day5b ./sample.txt
	./day5b ./input.txt
	
clean:
	rm -f day5 *.o
