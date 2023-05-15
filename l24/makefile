CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

main: main_o tree_o
	$(CC) $(CFLAGS) -o main.out main.o tree.o
main_o:
	$(CC) $(CFLAGS) -c main.c
tree_o:
	$(CC) $(CFLAGS) -c tree.c
clean:
	rm -f main.out *.o