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
int front = 0;
int rear = 0;

void queuePrint();
element stackEmpty();
void queueFull();
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
	int i = front;
	while (i != rear) {
		i = (i + 1) % MAX_QUEUE_SIZE;
		printf("%d, %s\n", queue[i].id, queue[i].name);
	}
	printf("\n");
}

void queueEmpty() {
	fprintf(stderr, "queue is empty\n\n");
	exit(EXIT_FAILURE);
}

void queueFull(){
	fprintf(stderr, "queue is full, not added\n");
}

void addq(element item) {
	int temp;
	temp = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == temp) {
		queueFull();
	}
	else {
		rear = temp;
		queue[rear] = item;
	}
}

element deleteq() {
	if (front == rear) {
		queueEmpty();
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}