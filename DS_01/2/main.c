#include <stdio.h>

int sumAry2D_f1(int ary[][3], int ROW, int COL) {
	int sum = 0, rows = 0, columns = 0;
	for (rows = 0; rows < ROW; ++rows) {
		for (columns = 0; columns < COL; ++columns) {
			sum = sum + ary[rows][columns];
		}
	}
	return sum;
}

int sumAry2D_f2(int (*ary)[3], int ROW) {
	int sum = 0, rows = 0;
	int *columns;
	for (rows = 0; rows < ROW; ++rows) {
		for (columns = ary[rows]; columns < ary[rows + 1]; ++columns) {
			sum = sum + *columns;
		}
	}
	return sum;
}

int sumAry2D_f3(int ary[2][3]) {
	int sum = 0, rows, columns, ROW = 2, COLUMN = sizeof(ary[0]) / sizeof(ary[0][0]);
	for (rows = 0; rows < ROW; ++rows) {
		for (columns = 0; columns < COLUMN; ++columns) {
			sum = sum + ary[rows][columns];
		}
	}
	return sum;
}

int main(void) {
	int ary2D[][3] = { {1, 2, 3}, {4, 5, 6} };

	printf("sumAry2D_f1() %d \n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d \n", sumAry2D_f2(ary2D, 2));
	printf("sumAry2D_f3() %d \n", sumAry2D_f3(ary2D));
	return 0;
}