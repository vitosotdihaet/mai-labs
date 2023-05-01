CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

main: main.o stack.o
	$(CC) $(CFLAGS) -o main.out main.o stack.o
main_o:
	$(CC) $(CFLAGS) -c main.c
stack_o:
	$(CC) $(CFLAGS) -c stack.c
clean:
	rm -f *.o main.out