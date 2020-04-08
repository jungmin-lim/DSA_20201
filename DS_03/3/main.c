#include <stdio.h>
#include <stdlib.h>
#define EXIT_FAILURE -1
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

int sumAry2D_f1(int ary[][3], int rows, int cols) {
	int i, j, sum = 0;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			sum = sum + ary[i][j];
		}
	}
	return sum;
}

int sumAry2D_f2(int (*ary)[3], int rows, int cols) {
	int i, j, sum = 0;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			sum = sum + ary[i][j];
		}
	}
	return sum;
}

int sumAry2D_f3(int ary[][3], int rows, int cols) {
	int i, j, sum = 0;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			sum = sum + ary[i][j];
		}
	}
	return sum;
}

int sumAry2D_f4(int **ary, int rows, int cols) {
	int i, j, sum = 0;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			sum = sum + ary[i][j];
		}
	}
	return sum;
}

int sumAry2D_f5(int ***ary, int rows, int cols) {
	int i, j, sum = 0;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			sum = sum + *((*ary)[i] +j);
		}
	}
	return sum;
}

void freeAry2D(int ***ary, int rows) {
	int i;
	for (int i = 0; i < rows; ++i) {
		free(ary[i]);
	}
	free(ary);
}

int main(void) {
	int ary2D[][3] = { {1, 2, 3},
						{4, 5, 6} };
	int r, c;
	int **ary = (int **)malloc(sizeof(int *) * 2);
	for (r = 0; r < 2; ++r) {
		ary[r] = (int *)malloc(sizeof(int) * 3);
	}
	for (r = 0; r < 2; ++r) {
		for (c = 0; c < 3; ++c) {
			ary[r][c] = r + c;
		}
	}

	// 정적 배열
	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f1(ary2D, 2, 3));

	// 동적 배열
	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary, 2, 3));

	freeAry2D(ary, 2);
	return 0;
}