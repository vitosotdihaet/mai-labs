CC = gcc
CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op  -Wpointer-arith -Wstack-usage=8192 -Wstrict-aliasing -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE

main:
	$(CC) $(CFLAGS) -o main.out main.c -lm
	./main.out
