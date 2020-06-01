#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 80
#define MAX_RECORD 100

typedef struct record {
	int key;
	char name[MAX_NAME];
	int grade;
};

void insert(struct record r, struct record records[], int i);
void insertionSort(struct record records[], int n);

int main(int argc, char *argv[]) {
	FILE *fp;
	struct record records[MAX_RECORD];
	int size;
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &size);

	for (i = 1; i <= size; ++i) {
		fscanf(fp, "%d %s %d", &records[i].key, records[i].name, &records[i].grade);
	}

	fprintf(stdout, "<<<<<<<<<< Input List >>>>>>>>>>\n");
	for (i = 1; i <= size; ++i) {
		fprintf(stdout, "(%d, %s, %d)\n", records[i].key, records[i].name, records[i].grade);
	}

	insertionSort(records, size);
	fprintf(stdout, "\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (i = 1; i < size+1; ++i) {
		fprintf(stdout, "(%d, %s, %d)\n", records[i].key, records[i].name, records[i].grade);
	}
	fclose(fp);
	return 0;
}

void insert(struct record r, struct record records[], int i) {
	records[0] = r;
	while (r.key < records[i].key) {
		records[i + 1] = records[i];
		--i;
	}
	records[i + 1] = r;
}

void insertionSort(struct record records[], int n) {
	int j;
	for (j = 2; j <= n; ++j) {
		struct record temp = records[j];
		insert(temp, records, j - 1);
	}
}