#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void inc_insertion_sort(int list[], int first, int last, int gap);
void shell_sort(int list[], int n);

int main(int argc, char *argv[]) {
	FILE *fp;
	int list[MAX_SIZE], size;
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &size);

	for (i = 0; i < size; ++i) {
		fscanf(fp, "%d", &list[i]);
	}

	fprintf(stdout, "list[] data\n");
	for (i = 0; i < size; ++i) {
		fprintf(stdout, "%5d", list[i]);
	}
	fprintf(stdout, "\n");

	shell_sort(list, size);
	fclose(fp);
	return 0;
}

void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; ++i) {
			inc_insertion_sort(list, i, n - 1, gap);
		}

		fprintf(stdout, "\ngap is %5d ====>\n", gap);
		for (i = 0; i < n; ++i) {
			fprintf(stdout, "%5d", list[i]);
		}
		fprintf(stdout, "\n");
	}
}