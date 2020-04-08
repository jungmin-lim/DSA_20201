#include <stdio.h>

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int compare(int x, int y) {
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

void selectionSort(int array[], int size) {
	int minIndex = 100, i = 0, j = 0;
	for (i = 0; i < size-1; ++i) {
		minIndex = i;
		for (j = i + 1; j < size; ++j) {
			if (array[j] < array[minIndex]) {
				minIndex = j;
			}
		}
		swap(&array[i], &array[minIndex]);
	}
}

int binSearch(int array[], int key, int left, int right) {
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(array[middle], key)) {
			case -1: left = middle + 1;
				break;
			case 0: return middle;
			case 1: right = middle - 1;
		}
	}
	return -1;
}

int binarySearch(int array[], int size, int key) {
	return binSearch(array, key, 0, size-1);
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