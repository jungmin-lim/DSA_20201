#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 20
#define MAX_STACK_SIZE 5

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

void stackPrint();
void stackEmpty();
void stackFull();
void push(element item);
element pop();

int main(void) {
	char input[80];
	char *tok = NULL, *next_str;
	char *delimiter = " \n";
	element student;

	printf("<< stack operations where MAX_STACK_SIZE is 5>>\n");
	printf("The format of the stack operation is as follows!!\n");
	printf("push 1 Jung\n");
	printf("pop\n\n");
	printf("***************************************************\n");

	while (1) {
		gets_s(input, sizeof(input));
		tok = strtok_s(input, delimiter, &next_str);
		if (tok == NULL) continue;
		if (!strcmp(tok, "push")) {
			sscanf_s(input + strlen(tok) + 1, "%d%s", &student.id, student.name, sizeof(student.name));
			push(student);
		}
		else if (!strcmp(tok, "pop")) {
			pop();
		}
		else if (!strcmp(tok, "sprint")) {
			stackPrint();
		}
		else {
			fprintf(stderr, "wrong command! try again!\n");
		}
	}
	return 0;
}

void stackPrint() {
	int i;
	for (i = top; i >= 0; --i) {
		printf("%d %s\n", stack[i].id, stack[i].name);
	}
	printf("\n");
}

void stackEmpty() {
	fprintf(stderr, "Stack is empty, cannot delete element\n");
	exit(EXIT_FAILURE);
}

void stackFull() {
	fprintf(stderr, "Stack is full, cannot add element\n");
	stackPrint();
	exit(EXIT_FAILURE);
}

void push(element item) {
	if (top >= MAX_STACK_SIZE-1) {
		stackFull();
	}
	stack[++top] = item;
}

element pop() {
	if (top == -1) {
		stackEmpty();
	}
	return stack[top--];
}