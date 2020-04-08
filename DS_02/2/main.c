#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "selectionSort.h"
#define MAX_SIZE 1001

void main(void) {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	clock_t start;
	FILE *fp;
	fp = fopen("out.txt", "w");
	if (fp == NULL) {
		perror("Error opening file");
		return(-1);
	}

	fprintf(fp, "	n	time\n");
	for (n = 0; n <= 1000; n += step) {
		for (i = 0; i < n; ++i) {
			a[i] = n - i;
		}
		start = clock();
		selectionSort(a, n);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		fprintf(fp,"%6d		%f\n", n, duration);
		if (n == 100) step = 100;
	}
	fclose(fp);
	return 0;
}