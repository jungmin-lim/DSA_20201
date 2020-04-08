#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 10000
#define MAX_MAZE_SIZE 1000

typedef struct {
	short int row;
	short int column;
	short int dir;
}element;

typedef struct {
	short int vert;
	short int horiz;
}offsets;

element stack[MAX_STACK_SIZE];
offsets move[8] = {
	{-1, 0},
	{-1, 1},
	{0, 1},
	{1, 1},
	{1, 0},
	{1, -1},
	{0, -1},
	{-1, -1}
};

short int maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
short int mark[MAX_MAZE_SIZE][MAX_MAZE_SIZE] = { 0 };
int top = -1;
int EXIT_ROW, EXIT_COL;

void stackEmpty();
void stackFull();
void push(element item);
element pop();
void path(void);

int main(void) {
	FILE *f;
	int row, col, i, j;

	// Build maze
	f = fopen("input.txt", "r");
	fscanf(f, "%d %d", &row, &col);

	EXIT_ROW = row + 1; EXIT_COL = col + 1;
	for (i = 0; i < col + 1; ++i) {
		maze[0][i] = 1;
	}
	for (i = 1; i <= row; ++i) {
		maze[i][0] = 1;
		for (j = 1; j <= col; ++j) {
			fscanf(f, "%d", &maze[i][j]);
		}
		maze[i][col+1] = 1;
	}
	for (i = 0; i < col + 1; ++i) {
		maze[row + 1][i] = 1;
	}

	path();
	fclose(f);
	return 0;
}

void stackEmpty() {
	fprintf(stderr, "Stack is empty, cannot delete element\n");
	exit(EXIT_FAILURE);
}

void stackFull() {
	fprintf(stderr, "Stack is full, cannot add element\n");
	exit(EXIT_FAILURE);
}

void push(element item) {
	if (top >= MAX_STACK_SIZE-1) {
		stackFull();
	}
	stack[++top] = item;
}

element pop() {
	if (top == -1) {
		stackEmpty();
	}
	return stack[top--];
}

void path() {
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].column = 1; stack[0].dir = 1;
	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.column; dir = position.dir;

		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;

			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				found = TRUE;
			}

			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.column = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}

			else ++dir;
		}
	}

	if (found) {
		printf("The path is: \n");
		printf("row  col\n");
		for (i = 0; i <= top; ++i) {
			printf("%2d%5d\n", stack[i].row, stack[i].column);
		}
		printf("%2d%5d\n", row, col);
	}
	else {
		printf("The maze does not have a path\n");
	}
}
