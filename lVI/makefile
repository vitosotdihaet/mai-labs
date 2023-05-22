CC = gcc
CFLAGS = -Wall -Wextra

main: main.o db.o
	$(CC) $(CFLAGS) -o main.out main.o db.o -lm
bad: bad.o db.o
	$(CC) $(CFLAGS) -o bad.out bad.o db.o
main_o: db.o
	$(CC) $(CFLAGS) -c main.c
bad_o:
	$(CC) $(CFLAGS) -c bad.c
db_o:
	$(CC) $(CFLAGS) -c db.c -lm
clean:
	rm -f *.o *.out