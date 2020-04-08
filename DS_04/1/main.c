#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int col;
	int row;
	int value;
}term;

void makeTerms(term *terms, int matrix[][20]) {
	int i, j, k = 1 ;
	for (i = 0; i < 20; ++i) {
		for (j = 0; j < 20; ++j) {
			if (matrix[i][j] != 0) {
				terms[k].row = i;
				terms[k].col = j;
				terms[k].value = matrix[i][j];
				++k;
			}
		}
	}
}

void printMatrix(int matrix[][20]) {
	int i, j;
	for (i = 0; i < 20; ++i) {
		for (j = 0; j < 20; ++j) {
			printf("%6d", matrix[i][j]);
		}
		printf("\n");
	}
}

void printTerms(term *terms, int size) {
	int i, j;
	for (i = 0; i < size; ++i) {
		printf("%6d, %6d %6d\n", terms[i].row, terms[i].col, terms[i].value);
	}
}

int main(void) {

	int n, i, j, r, c, v;
	int sparseArray[20][20] = { 0 };
	term *terms;

	srand(time(0));
	printf("원소의 개수를 쓰시오 .. ");
	scanf("%d", &n);
	terms = (term *)malloc(sizeof(term)*(n+1));
	terms[0].col = 20;
	terms[0].row = 20;
	terms[0].value = n;
	j = 1;

	for (i = 0; i < n; ++i) {
		while (1) {
			r = rand() % 20;
			c = rand() % 20;
			v = rand() % 100;
			if (sparseArray[r][c] == 0) {
				sparseArray[r][c] = v;
				break;
			}
		}
	}
	makeTerms(terms, sparseArray);
	printf("Random generated Matrix(20,20)\n");
	printMatrix(sparseArray);
	printf("sparce matrix\n");
	printTerms(terms, n+1);

	free(terms);
	return 0;
}