CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

main: main.o
	$(CC) $(CFLAGS) -o main.out main.o
main_o:
	$(CC) $(CFLAGS) -c main.c
clean:
	rm -f *.o main.out