#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUES 3

typedef struct {
	int id;
	int grade;
}element;

typedef struct queue *queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
}Node;

queuePointer front[MAX_QUEUES] = { NULL };
queuePointer rear[MAX_QUEUES] = { NULL };

void addQueue(int i, element item);
element deleteQueue(int i);
void queueEmpty();
void printQueue();
int main(int argc, char *argv[]) {
	FILE *f;
	int i;
	element item;
	f = fopen("input.txt", "r");
	while (fscanf(f, "%d %d %d", &i, &item.id, &item.grade) != EOF) {
		addQueue(i, item);
	}
	printQueue();
	return 0;
}

void addQueue(int i, element item) {
	queuePointer newNode;
	if ((newNode = (queuePointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}

	newNode->data = item;
	newNode->link = NULL;
	if (front[i]) {
		rear[i]->link = newNode;
	}
	else {
		front[i] = newNode;
	}
	rear[i] = newNode;
}

element deleteQueue(int i) {
	queuePointer temp = front[i];
	element item;
	if (!temp) {
		queueEmpty();
	}
	item = temp->data;
	front[i] = temp->link;
	free(temp);
	return item;
}

void queueEmpty() {
	fprintf(stderr, "queue empty");
	exit(EXIT_FAILURE);
}

void printQueue() {
	int i;
	element item;
	printf("과목번호, 학번, 성적\n");
	for (i = 0; i < MAX_QUEUES; ++i) {
		printf("**********************\n");
		while (front[i]) {
			item = deleteQueue(i);
			printf("%8d %5d %5d\n", i, item.id, item.grade);
		}
	}
}
