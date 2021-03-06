#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct record {
	int key;
};

int s, try = 0;

void swap(int *i, int *j);
void printList(int list[]);
void quickSort(int list[], int left, int right);

int main(int argc, char *argv[]) {
	FILE *fp;
	struct record list[MAX_SIZE];
	int size;
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &size);
	s = size;

	for (i = 0; i < size; ++i) {
		fscanf(fp, "%d", &list[i].key);
	}

	fprintf(stdout, "<<<<<<<<< Input List >>>>>>>>>>\n");
	for (i = 0; i < size; ++i) {
		fprintf(stdout, "%d ", list[i].key);
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "\nexecution of quick sort....\n");
	quickSort(list, 0, size-1);

	fprintf(stdout, "\ncalls of quick sort: %d\n", try);

	fprintf(stdout, "\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	printList(list);

	fclose(fp);
	return 0;
}

void swap(int *i, int *j) {
	int temp = *i;
	*i = *j;
	*j = temp;
}

void printList(struct record list[]) {
	int i;
	for (i = 0; i < s; ++i) {
		fprintf(stdout, "%d ", list[i].key);
	}
	fprintf(stdout, "\n");
}

void quickSort(struct record list[], int left, int right) {
	int pivot, i, j;
	int temp;

	if (left < right) {
		i = left; j = right + 1;
		pivot = list[left].key;
		do {
			do {
				i++;
			} while (list[i].key < pivot && i <= right);
			do {
				j--;
			} while (list[j].key > pivot && j >= left+1);

			if (i < j) swap(&list[i], &list[j]);
		} while (i < j);

		swap(&list[left], &list[j]);

		fprintf(stdout, "pivot = %d : ", pivot);
		try++;

		printList(list);
		quickSort(list, left, j - 1);
		quickSort(list, j + 1, right);
	}
}
