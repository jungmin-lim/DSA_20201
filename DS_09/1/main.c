#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACKS 3
typedef struct {
	int id;
	int grade;
}element;

typedef struct stack *stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
}Node;

stackPointer top[MAX_STACKS] = { NULL };

void push(int i, element item);
element pop(int i);
void stackEmpty();
void stackPrint();
int main(int argc, char *argv[]) {
	FILE *f;
	int i, id, score;
	element item;

	f = fopen("input.txt", "r");
	while (fscanf(f, "%d %d %d", &i, &id, &score) != EOF) {
		item.id = id;
		item.grade = score;
		push(i, item);
	}
	stackPrint();
	fclose(f);
	return 0;
}

void push(int i, element item) {
	stackPointer newNode;
	if ((newNode = (stackPointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient Error");
		exit(EXIT_FAILURE);
	}
	newNode->data = item;
	newNode->link = top[i];
	top[i] = newNode;
}

element pop(int i) {
	stackPointer temp;
	element item;
	temp = top[i];
	if (!temp) {
		stackEmpty();
	}
	item = temp->data;
	top[i] = temp->link;
	free(temp);
	return item;
}

void stackEmpty() {
	fprintf(stderr, "stack empty!");
	exit(EXIT_FAILURE);
}

void stackPrint() {
	int i;
	element item;
	printf("과목번호, 학번, 성적\n");
	for (i = 0; i < MAX_STACKS; ++i) {
		printf("*********************\n");
		while (top[i]) {
			item = pop(i);
			printf("%8d %5d %5d\n", i, item.id, item.grade);
		}
	}
}
