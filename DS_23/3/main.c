#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct element{
	int key;
}element;

int s, top = -1;  stack[MAX_SIZE];

void swap(element *a, element *b);
void heapSort(element a[], int n);
void adjust(element a[], int root, int n);

int main(int argc, char *argv[]) {
	FILE *fp;
	element heap[MAX_SIZE];
	int size;
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &size);
	s = size;

	for (i = 1; i <= size; ++i) {
		fscanf(fp, "%d", &heap[i].key);
	}

	fprintf(stdout, "<<<<<<<<<< Input List >>>>>>>>>>\n");
	for (i = 1; i <= size; ++i) {
		fprintf(stdout, "%d ", heap[i].key);
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "\n<<<<<<<<<< executing heap sort >>>>>>>>>>\n");
	heapSort(heap, size);
	
	fprintf(stdout, "\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (i = 1; i <= size; ++i) {
		fprintf(stdout, "%d ", heap[i].key);
	}
	fprintf(stdout, "\n");
	fclose(fp);
	return 0;
}

void swap(element *a, element *b) {
	element temp = *a;
	*a = *b;
	*b = temp;
}

void heapSort(element a[], int n) {
	int i, j;
	element temp;

	for (i = n / 2; i > 0; --i) {
		adjust(a, i, n);
	}

	fprintf(stdout, "after initialization of max heap...\n");
	for (i = 1; i <= n; ++i) {
		fprintf(stdout, "%d ", a[i].key);
	}
	fprintf(stdout, "\n\n\n");

	for (i = n - 1; i > 0; --i) {

		fprintf(stdout, "step %2d: Ãâ·Â %d :", n - i, a[1].key);
		swap(&a[1], &a[i + 1]);
		adjust(a, 1, i);
		for (j = 1; j <= i; ++j) {
			fprintf(stdout, "%4d", a[j].key);
		}
		fprintf(stdout, "\n");
	}
	
}

void adjust(element a[], int root, int n) {
	int child, rootkey;
	element temp;

	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;

	while (child <= n) {

		if ((child < n) && (a[child].key < a[child+1].key)) {
			child++;
		}

		if (rootkey > a[child].key) break;

		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}

	a[child / 2] = temp;
}