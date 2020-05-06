#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200
#define HEAP_FULL(n) (n == MAX_ELEMENT - 1)
#define HEAP_EMPTY(n) (!n)

int heap[MAX_ELEMENT];
int n = 0;

void push(int item, int *n) {
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item > heap[i / 2])) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

int pop(int *n) {
	int parent, child;
	int item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "Heap Empty!");
		exit(EXIT_FAILURE);
	}

	item = heap[1];
	temp = heap[(*n)--];

	parent = 1;
	child = 2;

	while (child <= *n) {
		if ((child < *n) && (heap[child] < heap[child + 1])) {
			child++;
		}
		if (temp >= heap[child]) break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

int main(int argc, char *argv[]) {
	FILE *f;
	int dat, i;
	f = fopen("input.txt", "r");

	printf("***** Insertion into a max heap *****\n");
	while (fscanf(f, "%d", &dat) != EOF) {
		push(dat, &n);
		for (i = 1; i <= n; ++i) {
			printf("%d ", heap[i]);
		}
		printf("\n");
	}
	printf("***** Deletion from a max heap ****\n");
	while (!HEAP_EMPTY(n)) {
		dat = pop(&n);
		printf("delete data = %d\n", dat);
		for (i = 1; i <= n; ++i) {
			printf("%d ", heap[i]);
		}
		printf("\n");
	}
}