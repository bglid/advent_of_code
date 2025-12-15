CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -O0

day2: day2.o 
	$(CC) $(CFLAGS) -o day2 day2.o 

day2b: day2b.o
	$(CC) $(CFLAGS) -o day2b day2b.o

run: day2
	# ./day2 ./sample.txt
	# ./day2 ./input.txt
	./day2b ./sample.txt
	./day2b ./input.txt
	
clean:
	rm -f day2 *.o
#
