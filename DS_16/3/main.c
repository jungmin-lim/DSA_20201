#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500
#define MAX_SPACE 1024

int makeWinnerTree(int wTree[], int arr[], int size);
void changeWinner(int arr[], int winner, int size);
void inorder(int wTree[], int idx, int size);
void makeArr(int *sorted[], int sortedIdx[], int arr[], int size);
void increaseIdx(int sortedIdx[], int ar[], int winner, int size);

int main(int argc, char *argv[]) {
	int i, j, k, n, seed, random, winner;
	int wTree[MAX_SPACE], arr[MAX_SPACE], sorted[MAX_SPACE][10], treeSorted[MAX_SPACE][10];
	int sortedIdx[10] = { 0 };

	fprintf(stdout, "%s", "the number of keys ( 4, 8, 16, or 32 as a power of 2 ) >> ");
	scanf("%d", &n);
	fprintf(stdout, "%s", "seed value : ");
	scanf("%u", &seed);
	srand(seed);

	for (k = 0; k < n; ++k) {
		random = rand() % MAX_SIZE;
		sorted[k][0] = random;

		for(i = 1; i < 10; ++i){
			sorted[k][i] = sorted[k][0] + i;
		}
	}

	printf("initial records\n");
	for (i = 0; i < n; ++i) {
		fprintf(stdout, "%d-th run:\n", i+1);
		for (j = 0; j < 10; ++j) {
			fprintf(stdout, "%4d", sorted[i][j]);
		}
		fprintf(stdout, "\n");
	}

	for (i = 0; i < n; ++i) {
		for (j = 0; j < 10; ++j) {
			makeArr(sorted, sortedIdx, arr, n);
			winner = makeWinnerTree(wTree, arr, n);
			treeSorted[i][j] = winner;
			increaseIdx(sortedIdx, arr, winner, n);
		}
	}

	fprintf(stdout, "\nsorting with min-winner tree...\n");
	fprintf(stdout, "\nsorted result\n");
	for (i = 0; i < n; ++i) {
		for (j = 0; j < 10; ++j) {
			fprintf(stdout, "%4d", treeSorted[i][j]);
		}
		fprintf(stdout, "\n");
	}

	return 0;
}

int makeWinnerTree(int wTree[], int arr[], int size) {
	int i;
	for (i = 0; i < size; ++i) {
		wTree[size + i] = arr[i];
	}

	while (size > 1) {
		for (i = size; i < size*2; i = i + 2) {
			wTree[i / 2] = min(wTree[i], wTree[i + 1]);
		}
		size = size / 2;
	}

	return wTree[1];
}

void makeArr(int sorted[][10], int sortedIdx[], int arr[], int size) {
	int i;
	for (i = 0; i < size; ++i) {
		if (sortedIdx[i] < 10) {
			arr[i] = sorted[i][sortedIdx[i]];
		}
		else {
			arr[i] = 9999;
		}
	}
}

void increaseIdx(int sortedIdx[], int arr[], int winner, int size) {
	int i;
	for (i = 0; i < size; ++i) {
		if (arr[i] == winner) {
			sortedIdx[i] += 1;
			break;
		}
	}
}
void inorder(int wTree[], int idx, int size) {
	if (idx < size*2) {
		inorder(wTree, idx * 2, size);
		fprintf(stdout, "%5d", wTree[idx]);
		inorder(wTree, idx * 2 + 1, size);
	}
}