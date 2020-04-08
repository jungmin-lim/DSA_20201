#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_COL 1000

typedef struct {
	int col;
	int row;
	int value;
}term;

void fastTranspose(term a[], term b[]) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0) {
		for (i = 0; i < numCols; ++i) {
			rowTerms[i] = 0;
		}
		for (i = 1; i <= numTerms; ++i) {
			rowTerms[a[i].col]++;
		}
		startingPos[0] = 1;
		for (i = 1; i < numCols; ++i) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}
		for (i = 1; i <= numTerms; ++i) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

void printMatrix(term terms[]) {
	int i, j, k = 1, m = terms[0].row, n = terms[0].value;
	
	for (i = 0; i < m; ++i) {
		for (j = 0; j < m; ++j) {
			if ((i == terms[k].row) && (j == terms[k].col)) {
				printf("%4d", terms[k].value);
				k++;
			}
			else {
				printf("   0");
			}
		}
		printf("\n");
	}
}

int main(void) {
	
	int i, j = 1, r, c, v;
	FILE *f;
	term *terms, *transposedTerms;
	f = fopen("a.txt", "r");
	fscanf(f, "%d %d %d", &r, &c, &v);
	
	terms = (term *)malloc(sizeof(term) * (v + 1));
	transposedTerms = (term *)malloc(sizeof(term) * (v + 1));
	terms[0].row = r;
	terms[0].col = c;
	terms[0].value = v;

	for (i = 0; i < v; ++i) {
		fscanf(f, "%d %d %d", &terms[j].row, &terms[j].col, &terms[j].value);
		j++;
	}
	fclose(f);

	fastTranspose(terms, transposedTerms);
	f = fopen("b.txt", "w");

	for (i = 0; i < v+1; ++i) {
		fprintf(f, "%3d %3d %4d\n", transposedTerms[i].row, transposedTerms[i].col, transposedTerms[i].value);
	}

	printf("A\n");
	printMatrix(terms);
	printf("B\n");
	printMatrix(transposedTerms);

	free(terms);
	free(transposedTerms);
	fclose(f);

	return 0;
}