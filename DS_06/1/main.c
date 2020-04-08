#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element *queue;
int front = 0, rear = 0;
int capacity = 2;

void printQueue();
void queueFull(); 
void copy(element *a, element *b, element *c);
void addQueue(element item);
void queueEmpty();
element deleteQueue();

int main(void) {
	char input[80];
	char *tok = NULL, *next_str;
	char *delimiter = " \n";
	element student;

	if ((queue = (element *)malloc(capacity * sizeof(element))) == NULL) {
		fprintf(stderr, "Insufficient Memory!\n");
		exit(EXIT_FAILURE);
	}

	printf("<< circular queue operations using dynamic allocation array, where the initial capacity is 2>>\n");
	printf("add 1 Jung\n");
	printf("delete\n\n");
	printf("***************************************************\n");

	while (1) {
		gets_s(input, sizeof(input));
		tok = strtok_s(input, delimiter, &next_str);
		if (tok == NULL) continue;
		if (!strcmp(tok, "add")) {
			sscanf_s(input + strlen(tok) + 1, "%d%s", &student.id, student.name, sizeof(student.name));
			addQueue(student);
		}
		else if (!strcmp(tok, "delete")) {
			student = deleteQueue();
		}
		else if (!strcmp(tok, "qprint")) {
			printQueue();
		}
		else {
			fprintf(stderr, "wrong command! try again!\n");
		}
	}
	return 0;
}


void printQueue() {
	int i = front;
	while (i != rear) {
		i = (i + 1) % capacity;
		printf("%d, %s\n", queue[i].id, queue[i].name);
	}
	printf("\n");
}

void queueFull() {
	int start;
	element *newQueue;
	if ((newQueue = (element *)malloc(sizeof(element) * 2 * capacity)) == NULL) {
		fprintf(stderr, "Insufficient Memory\n");
		exit(EXIT_FAILURE);
	}
	start = (front + 1) % capacity;

	if (start < 2) {
		copy(queue + start, queue + start + capacity - 1, newQueue);
	}

	else {
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity = 2 * capacity;
	printf("queue capacity is doubled,\n");
	printf("current queue capaicty is %d.\n", capacity);
	free(queue);
	queue = newQueue;
}

void copy(element *a, element *b, element *c) {
	while (a != b) {
		*c++ = *a++;
	}
}

void addQueue(element item) {
	rear = (rear+1) % capacity;
	if (front == rear) {
		queueFull();
		queue[++rear] = item;
	}
	else {
		queue[rear]= item;
	}
}

void queueEmpty() {
	fprintf(stderr, "queue is Empty\n");
	exit(EXIT_FAILURE);
}

element deleteQueue() {
	if (front == rear) {
		queueEmpty();
	}

	front = (front + 1) % capacity;
	return queue[front - 1];
}
