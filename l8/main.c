/* Лабораторная работа 8, вариант n.
 * Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>

// returns 0 if noone won, 1 if cross won, 2 if circle won
short int check(short int grid[3][3]) {
	// check rows
	for (short int i = 0; i < 3; ++i) {
		if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
			if (grid[i][0] == 1) { return 1; }
			if (grid[i][0] == 2) { return 2; }
		}
	}
	// check columns
	for (short int i = 0; i < 3; ++i) {
		if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
			if (grid[0][i] == 1) { return 1; }
			if (grid[0][i] == 2) { return 2; }
		}
	}
	// check diagonals
	if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
		if (grid[0][0] == 1) { return 1; }
		if (grid[0][0] == 2) { return 2; }
	}
	if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
		if (grid[0][2] == 1) { return 1; }
		if (grid[0][2] == 2) { return 2; }
	}
	// check for tie
	for (short int i = 0; i < 3; ++i) {
		for (short int j = 0; j < 3; ++j) {
			if (grid[i][j] == 0) { return 0; }
		}
	}

	return -1;
}

short int check_coords(short int x, short int y, short int grid[3][3]) {
	if (4 > x && x > 0 && 4 > y && y > 0) {
		if (grid[y - 1][x - 1] == 0) {
			return 1;
		} else {
			printf("The cell is already occupied!\n");
			return 0;
		}
	} else {
		printf("x or y is out of range!\n");
		return 0;
	}
}

void print(short int grid[3][3]) {
	printf("  1 2 3\n");
	for (short int i = 0; i < 3; ++i) {
		printf("%hu|", i + 1);
		for (short int j = 0; j < 3; ++j) {
			if (grid[i][j] == 0) { printf("_ "); }
			if (grid[i][j] == 1) { printf("X "); }
			if (grid[i][j] == 2) { printf("O "); }
		}
		printf("\n");
	}
}


int main() {
	short int grid[3][3];
	for (short int i = 0; i < 3; ++i) {
		for (short int j = 0; j < 3; ++j) {
			grid[i][j] = 0;
		}
	}

	short int x = -1, y = -1, current_player = 1, win = 0;

	while (win == 0) {
		system("clear");
		switch (current_player) {
			case 1: printf("X's turn!"); break;
			case 2: printf("O's turn!"); break;
		}
		printf("\n");
		print(grid);

		printf("Input x (horizontal) and y (vertical):\n");
		scanf("%hu %hu", &x, &y);
		while (check_coords(x, y, grid) == 0) {
			printf("Try again:\n");
			scanf("%hu %hu", &x, &y);
		}
		
		grid[y - 1][x - 1] = current_player;
		current_player = current_player % 2 + 1;

		win = check(grid);
	}

	system("clear");
	print(grid);

	switch (win) {
		case -1: printf("Tie!");   break;
		case  1: printf("X win!"); break;
		case  2: printf("O win!"); break;
	}
	printf("\n");

	return 0;
}
