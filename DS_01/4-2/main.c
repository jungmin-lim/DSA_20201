#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) =(t))
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y))? 0: 1)

void selectionSort(int array[], int size) {
	int minIndex = 100, i = 0, j = 0, temp;
	for (i = 0; i < size - 1; ++i) {
		minIndex = i;
		for (j = i + 1; j < size; ++j) {
			if (array[j] < array[minIndex]) {
				minIndex = j;
			}
		}
		SWAP(array[i], array[minIndex], temp);
	}
}

int binSearch(int array[], int key, int left, int right) {
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(array[middle], key)) {
			case -1: return binSearch(array, key, middle + 1, right);
			case 0: return middle;
			case 1: return binSearch(array, key, left, middle-1);
		}
	}
	return -1;
}

int binarySearch(int array[], int size, int key) {
	return binSearch(array, key, 0, size - 1);
}

int main(void) {
	int i = 0, n = 0, key = 0, searchResult, array[100] = { 0 };
	printf("Enter the number of numbers to generate: ");
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		array[i] = rand() % 1000;
	}

	for (i = 0; i < n; ++i) {
		printf("%d\t", array[i]);
	}
	printf("\n\n");

	printf("Sorted array: \n");
	selectionSort(array, n);
	for (i = 0; i < n; ++i) {
		printf("%d\t", array[i]);
	}
	printf("\n\n");

	printf("Enter the number to search: ");
	scanf("%d", &key);
	searchResult = binarySearch(array, n, key);
	if (searchResult == -1) {
		printf("The search number is no present\n");
	}
	else {
		printf("The search number is present in list[%d]\n", searchResult);
	}
	return 0;
}