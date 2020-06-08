#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS 10
#define MAX_ELEMENT 100

typedef struct Queue *QueuePointer;
typedef struct Queue {
	int key;
	QueuePointer link;
}Queue;

int stack[BUCKETS][MAX_ELEMENT];
int top[BUCKETS] = { -1, -1, -1, -1, -1, -1 ,-1, -1, -1, -1 };
void init(QueuePointer *queue) {
	(*queue) = NULL;
	return;
}

int isEmpty(QueuePointer queue) {
	if (!queue) return 1;
	else return 0;
}

void enqueue(QueuePointer *queue, int data) {
	QueuePointer newNode, temp = (*queue);
	if ((newNode = (QueuePointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient Memory!\n");
		exit(EXIT_FAILURE);
	}
	newNode->key = data;
	newNode->link = NULL;

	if (isEmpty(temp)) {
		(*queue) = newNode;
		return;
	}
	
	while (temp->link != NULL) {
		temp = temp->link;
	}
	temp->link = newNode;

	return;
}

int dequeue(QueuePointer *queue) {
	QueuePointer temp = (*queue);
	int ret;
	if (isEmpty(temp)) {
		fprintf(stderr, "Queue Empty!\n");
		exit(EXIT_FAILURE);
	}

	(*queue) = temp->link;

	ret = temp->key;
	free(temp);
	return ret;
}

void push(int i, int data) {
	stack[i][++top[i]] = data;
}

int pop(int i) {
	int val;
	if (top[i] == -1) {
		fprintf(stdout, "stack empty!\n");
		exit(EXIT_FAILURE);
	}
	val = stack[i][top[i]--];
	return val;
}

int maxTop() {
	int i, val = 0;
	for (i = 0; i < BUCKETS; ++i) {
		if (top[i] > val) {
			val = top[i];
		}
	}
	return val;
}

void radixSort(int list[], int digits, int n) {
	int i, j, b, d, factor = 1, temp;
	QueuePointer queue[BUCKETS];

	for (b = 0; b < BUCKETS; ++b) {
		init(&queue[b]);
	}
	for (d = 0; d < digits; ++d) {
		for (i = 0; i < n; ++i) {
			enqueue(&queue[(list[i] / factor) % 10], list[i]);
		}

		fprintf(stdout, "step %d 의 자리 ---\n\n", d);
		fprintf(stdout, "Queue의 내용 ---\n");
		for (b = i = 0; b < BUCKETS; ++b) {
			while (!isEmpty(queue[b])) {
				temp = dequeue(&queue[b]);
				list[i++] = temp;
				push(b, temp);
			}
		}
		factor *= 10;

		temp = maxTop();
		for (i = 0; i < n; ++i) {
			fprintf(stdout, "%5d", i);
		}
		fprintf(stdout, "\n");
		for (i = temp+1; i >= 0; --i) {
			for (j = 0; j < n; ++j) {
				if (top[j] == i) {
					fprintf(stdout, "%5d", pop(j));
				}
				else {
					fprintf(stdout, "     ");
				}
			}
			fprintf(stdout, "\n\n");
		}
		fprintf(stdout, "------------------------------------------------------\n");
		for (i = 0; i < n; ++i) {
			fprintf(stdout, "%5d", list[i]);
		}
		fprintf(stdout, "\n\n");
	}
}

int main(int argc, char *argv[]) {
	FILE *fp;
	int digits, radix = 10, size;
	int data[MAX_ELEMENT], link[MAX_ELEMENT];
	int i;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &digits, &size);
	for (i = 0; i < size; ++i) {
		fscanf(fp, "%d", &data[i]);
	}

	fprintf(stdout, "input data ---\n");
	for (i = 0; i < size; ++i) {
		fprintf(stdout, "%5d", data[i]);
	}
	fprintf(stdout, "\n\n");
	
	radixSort(data, digits, size);

	fprintf(stdout, "result ---\n");
	for (i = 0; i < size; ++i) {
		fprintf(stdout, "%5d", data[i]);
	}
	fclose(fp);
	return 0;
}