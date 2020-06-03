#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

int s, sorted[MAX_SIZE];

void merge(int list[], int left, int mid, int right);
void mergeSort(int list[], int left, int right);

int rmergeSort(int a[], int link[], int left, int right);
int listMerge(int a[], int link[], int start1, int start2);

void printList(int list[]);

int main(int argc, char *argv[]) {
	FILE *fp;
	int size, list[MAX_SIZE];
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &size);
	s = size;

	for (i = 1; i <= size; ++i) {
		fscanf(fp, "%d", &list[i]);
	}

	fprintf(stdout, "<<<<<<<<<< Input List >>>>>>>>>>\n");
	printList(list);

	fprintf(stdout, "\n<<<<<<<<<< executing recursive merge sort >>>>>>>>>\n");
	mergeSort(list, 1, size);

	fprintf(stdout, "\n<<<<<<<<<< Sorted List >>>>>>>>>>>\n");
	printList(list);

	fclose(fp);
	return 0;
}

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
		}
		else {
			sorted[k++] = list[j++];
		}
	}

	if (i > mid) {
		for (l = j; l <= right; ++l) {
			sorted[k++] = list[l];
		}
	}
	else {
		for (l = i; l <= mid; ++l) {
			sorted[k++] = list[l];
		}
	}

	for (l = left; l <= right; ++l) {
		list[l] = sorted[l];
	}
}

void mergeSort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		mergeSort(list, left, mid);
		mergeSort(list, mid + 1, right);
		merge(list, left, mid, right);
		fprintf(stdout, "\ncall merge(list, left=%d, mid=%d, right=%d)\n", left, mid, right);
		fprintf(stdout, "result : ");
		printList(list);
	}
}

int rmergeSort(int a[], int link[], int left, int right) {
	int mid;
	if (left >= right) return left;
	mid = (left + right) / 2;
	return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}

int listMerge(int a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;

	for (last1 = start1, last2 = start2; last1 && last2;) {
		if (a[last1] <= a[last2]) {
			link[lastResult] = last1;
			lastResult = last1; last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2; last2 = link[last2];
		}
	}

	if (last1 == 0) {
		link[lastResult] = last2;
	}
	else {
		link[lastResult] = last1;
	}

	return link[0];
}

void printList(int list[]) {
	int i;
	for (i = 1; i <= s; ++i) {
		fprintf(stdout, "%d ", list[i]);
	}
	fprintf(stdout, "\n");
}