#include <stdio.h>
#include <stdlib.h>
#define EXIT_FAILURE -1
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}


int **make2dArray(int rows, int cols) {
	int i, j, **array;
	MALLOC(array, sizeof(*array) * rows);

	for (i = 0; i < rows; ++i) {
		MALLOC(array[i], sizeof(**array) * cols);
	}

	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			array[i][j] = rand() % 100;
		}
	}
	return array;
}

int main() {
	int **ipp;
	int i, j, rows, cols;
	printf("이차원 배열의 행과 열의 수를 입력하세요 : ");
	scanf("%d %d", &rows, &cols);
	ipp = make2dArray(rows, cols);
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			printf("ipp[%d] = %d ", i, ipp[i][j]);
		}
	}
	return 0;
}