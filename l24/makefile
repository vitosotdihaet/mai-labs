CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

main: main_o
	$(CC) $(CFLAGS) -o main.out main.o
main_o:
	$(CC) $(CFLAGS) -c main.c
clean:
	rm -f main.out *.o