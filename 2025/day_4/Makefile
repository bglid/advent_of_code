CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3 -O0

# day4: day4.o 
# 	$(CC) $(CFLAGS) -o day4 day4.o 

day4b: day4b.o
	$(CC) $(CFLAGS) -o day4b day4b.o

run: day4
	./day4 ./sample.txt
	./day4 ./input.txt
	./day4b ./sample.txt
	./day4b ./input.txt
	
clean:
	rm -f day4 *.o
