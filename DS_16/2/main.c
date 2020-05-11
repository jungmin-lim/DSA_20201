#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500
#define MAX_SPACE 1024

int makeWinnerTree(int wTree[], int arr[], int size);
void changeWinner(int arr[], int winner, int size);
void inorder(int wTree[], int idx, int size);

int main(int argc, char *argv[]) {
	int i, j, n, seed, random, winner;
	int wTree[MAX_SPACE], arr[MAX_SPACE], sorted[MAX_SPACE];

	fprintf(stdout, "%s", "the number of keys ( 4, 8, 16, or 32 as a power of 2 ) >> ");
	scanf("%d", &n);
	fprintf(stdout, "%s", "seed value : ");
	scanf("%u", &seed);
	srand(seed);

	for (i = 0; i < n; ++i) {
		while (1) {
			random = rand() % MAX_SIZE;
			fprintf(stdout, "%4d", random);
			arr[i] = random;
			break;
		}
	}

	fprintf(stdout, "\n\ninitialization of min-winner tree\n\n");
	for (i = 0; i < n; ++i) {
		winner = makeWinnerTree(wTree, arr, n);
		sorted[i] = winner;

		if (i == 0) {
			fprintf(stdout, "inorder traversal for min-winner tree\n");
			inorder(wTree, 1, n);
			fprintf(stdout, "\n");
		}
		if (i == 2) {
			fprintf(stdout, "Wninner tree inorder traversal after find 2 winners\n");
			inorder(wTree, 1, n);
			fprintf(stdout, "\n");
		}

		changeWinner(arr, winner, n);
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

void changeWinner(int arr[], int winner, int size) {
	int i;
	for (i = 0; i < size; ++i) {
		if (arr[i] == winner) {
			arr[i] = 9999;
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
