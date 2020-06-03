#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct element {
	int key;
}element;

int s;

void merge(element initList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);
void printList(element list[]);

int main(int argc, char *argv[]) {
	FILE *fp;
	element list[MAX_SIZE];
	int size;
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &size);
	s = size;

	for (i = 1; i <= size; ++i) {
		fscanf(fp, "%d", &list[i].key);
	}

	fprintf(stdout, "<<<<<<<<<< Input List >>>>>>>>>>\n");
	printList(list);

	fprintf(stdout, "\n<<<<<<<<<< executing iterative merge sort >>>>>>>>>>\n");
	mergeSort(list, size);

	fprintf(stdout, "\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	printList(list);

	fclose(fp);
	return 0;
}

void merge(element initList[], element mergedList[], int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].key <= initList[j].key) {
			mergedList[k++] = initList[i++];
		}
		else {
			mergedList[k++] = initList[j++];
		}
	}
	
	if (i > m) {
		for (t = j; t <= n; ++t) {
			mergedList[t] = initList[t];
		}
	}
	else {
		for (t = i; t <= m; ++t) {
			mergedList[k+t-i] = initList[t];
		}
	}
}

void mergePass(element initList[], element mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) {
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	}
	if (i + s - 1 < n) {
		merge(initList, mergedList, i, i + s - 1, n);
	}
	else {
		for (j = i; j <= n; ++j) {
			mergedList[j] = initList[j];
		}
	}
}

void mergeSort(element a[], int n) {
	int s = 1;
	element extra[MAX_SIZE];

	while (s < n) {
		mergePass(a, extra, n, s);
		fprintf(stdout, "\nsegment size : %d\n", s);
		fprintf(stdout, "%12s :", "a");
		printList(a);
		fprintf(stdout, "%12s :", "temp");
		printList(extra);
		s *= 2;
		mergePass(extra, a, n, s);
		fprintf(stdout, "\nsegment size : %d\n", s);
		fprintf(stdout, "%12s :", "temp");
		printList(extra);
		fprintf(stdout, "%12s :", "a");
		printList(a);
		s *= 2;
	}
}

void printList(element list[]) {
	int i;
	for (i = 1; i <= s; ++i) {
		fprintf(stdout, "%5d ", list[i]);
	}
	fprintf(stdout, "\n");
}