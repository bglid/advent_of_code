CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -O0

day3: day3.o 
	$(CC) $(CFLAGS) -o day3 day3.o 

day3b: day3b.o
	$(CC) $(CFLAGS) -o day3b day3b.o

run: day3
	# ./day3 ./sample.txt
	# ./day3 ./input.txt
	./day3b ./sample.txt
	./day3b ./input.txt
	
clean:
	rm -f day3 *.o
