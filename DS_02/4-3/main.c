#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "selectionSort.h"
#define MAX_SIZE 1001

void main(void) {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	FILE *fp;
	fp = fopen("out.txt", "w");
	if (fp == NULL) {
		perror("Error opening file");
		return(-1);
	}

	fprintf(fp, "  n	repetitions	time\n");
	for (n = 0; n <= 1000; n += step) {
		long repetitions = 0;
		clock_t start = clock();

		do {
			repetitions++;
			for (i = 0; i < n; ++i) {
				a[i] = rand()%10000;
			}
			selectionSort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		fprintf(fp, "%6d %9d  %f\n", n, repetitions, duration);
		if (n == 100) step = 100;
	}

	fclose(fp);
	return 0;
}