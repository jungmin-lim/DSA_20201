#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

void queuePrint();
element stackEmpty();
void queueFull(element item);
void dataShift();
void addq(element item);
element deleteq();

int main(void) {
	char input[80];
	char *tok = NULL, *next_str;
	char *delimiter = " \n";
	element student;

	printf("<< Circular queue operations where MAX_QUEUE_SIZE is 3>>\n");
	printf("add 1 Jung\n");
	printf("delete\n\n");
	printf("***************************************************\n");

	while (1) {
		gets_s(input, sizeof(input));
		tok = strtok_s(input, delimiter, &next_str);
		if (tok == NULL) continue;
		if (!strcmp(tok, "add")) {
			sscanf_s(input + strlen(tok) + 1, "%d%s", &student.id, student.name, sizeof(student.name));
			addq(student);
		}
		else if (!strcmp(tok, "delete")) {
			deleteq();
		}
		else if (!strcmp(tok, "qprint")) {
			queuePrint();
		}
		else {
			fprintf(stderr, "wrong command! try again!\n");
		}
	}
	return 0;
}

void queuePrint() {
	int i;
	for (i = front+1; i <= rear; ++i) {
		printf("%d %s\n", queue[i].id, queue[i].name);
	}
	printf("\n");
}

void queueEmpty() {
	fprintf(stderr, "queue is empty, cannot delete element.\n\n");
	exit(EXIT_FAILURE);
}

void queueFull(element item) {
	if (front == -1) {
		fprintf(stderr, "queue is full, not added\n");
	}
	else {
		printf("data shift\n");
		dataShift();
		addq(item);
	}
}

void dataShift() {
	int i = 0;
	for (i = front + 1; i <= rear; ++i) {
		queue[i - front - 1] = queue[i];
	}
	rear = rear - front - 1;
	front = -1;
}

void addq(element item) {
	if (rear == MAX_QUEUE_SIZE-1) {
		queueFull(item);
	}
	else {
		queue[++rear] = item;
	}
}

element deleteq() {
	if (front == rear) {
		queueEmpty();
	}
	return queue[front++];
}