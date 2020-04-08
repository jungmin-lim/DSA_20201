#pragma once

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void selectionSort(int array[], int size) {
	int i = 0, j = 0, minIdx, temp;
	for (i = 0; i < size - 1; ++i) {
		minIdx = i;
		for (j = 0; j < size; ++j) {
			if (array[j] < array[minIdx]) {
				minIdx = j;
			}
		}
		swap(&array[i], &array[minIdx]);
	}
}