#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 80
#define MAX_ELEMENT 100

typedef struct element {
	int key;
	char name[MAX_STRING];
	int grade;
}element;

void swap(element *a, element *b);
void bubble_sort(element list[], int n);
void printList(element list[], int n);

int main(int argc, char *argv[]) {
	FILE *fp;	
	element data[MAX_ELEMENT];
	int size;
	int i;

	fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &size);
	for (i = 0; i < size; ++i) {
		fscanf(fp, "%d %s %d", &data[i].key, data[i].name, &data[i].grade);
	}

	fprintf(stdout, "<<<<<<<<<< Input List >>>>>>>>>>\n");
	printList(data, size);

	bubble_sort(data, size);

	fprintf(stdout, "<<<<<<<<<< Result Sorted List >>>>>>>>>>\n");
	printList(data, size);

	fclose(fp);
	return 0;
}

void swap(element *a, element *b) {
	element temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void bubble_sort(element list[], int n) {
	int i, j;
	for (i = n - 1; i > 0; --i) {
		for (j = 0; j < i; j++) {
			if (list[j].key > list[j + 1].key) {
				swap(&list[j], &list[j + 1]);
			}
		}

		fprintf(stdout, "<<<<<<<<<< Step %d : Sorted List >>>>>>>>>>\n", n - i);
		printList(list, n);
	}
	return;
}

void printList(element list[], int n) {
	int i;
	for (i = 0; i < n; ++i) {
		fprintf(stdout, "( %d, %s, %d )\n", list[i].key, list[i].name, list[i].grade);
	}
	fprintf(stdout, "\n");
}