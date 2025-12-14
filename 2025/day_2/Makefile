CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -O0

day2: day2.o 
	$(CC) $(CFLAGS) -o day2 day2.o 


run: day2
	./day2 ./sample.txt
	./day2 ./input.txt
	
clean:
	rm -f day2 *.o
