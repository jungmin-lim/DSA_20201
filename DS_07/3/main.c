#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 10
#define MAX_STACKS 10
#define MAX_NAME_SIZE 20

typedef struct {
	char name[MAX_NAME_SIZE];
}element;

element memory[MEMORY_SIZE];
int top[MAX_STACKS];
int boundary[MAX_STACKS];
int n;

element stackEmpty(int i);
void stackFull(int i);
void push(int i, element item);
element pop(int i);
void printStack(int i);

int main(void) {
	char input[80];
	char *tok = NULL, *next_str;
	char *delimiter = " \n";
	element student;
	int i, j;

	printf("How many stacks? : ");
	scanf("%d", &n);
	top[0] = boundary[0] = -1;
	for (j = 1; j < n; ++j) {
		top[j] = boundary[j] = (MEMORY_SIZE / n) * j - 1;
	}
	boundary[n] = MEMORY_SIZE - 1;

	printf("\n C Language progarm to implement the Multiple Stacks\n");
	printf("add stack_num(0-2) name : add 0 kim\n");
	printf("delete stack_num(0-2) : delete 0\n");
	printf("sprint stack_num(0-2) : sprint 0\n");
	printf("***************************************************\n\n");

	while (1) {
		gets_s(input, sizeof(input));
		tok = strtok_s(input, delimiter, &next_str);
		if (tok == NULL) continue;
		if (!strcmp(tok, "add")) {
			sscanf_s(input + strlen(tok) + 1, "%d%s", &i, student.name, sizeof(student.name));
			if (0 > i || i >= n) {
				fprintf(stderr, "stack number error, try again\n");
				continue;
			}
			push(i, student);
		}
		else if (!strcmp(tok, "delete")) {
			sscanf_s(input + strlen(tok) + 1, "%d", &i);
			if (0 > i || i >= n) {
				fprintf(stderr, "stack number error, try again\n");
				continue;
			}
			student = pop(i);
		}
		else if (!strcmp(tok, "sprint")) {
			sscanf_s(input + strlen(tok) + 1, "%d", &i);
			if (0 > i || i >= n) {
				fprintf(stderr, "stack number error, try again\n");
				continue;
			}
			printStack(i);
		}
		else {
			fprintf(stderr, "wrong command! try again!\n");
		}
		i = -1;
	}

	return 0;
}

element stackEmpty(int i) {
	element emptyElement;
	emptyElement.name[0] = '\0';
	fprintf(stderr, "Stack%d is Empty\n",i);
	return emptyElement;
}

void stackFull(int i) {
	fprintf(stderr, "Stack%d is Full\n", i);
}

void push(int i, element item) {
	if (top[i] == boundary[i+1]) {
		stackFull(i);
	}
	else {
		printf("%s is Pushed in Stack No. %d\n", item.name, i);
		memory[++top[i]] = item;
	}
}

element pop(int i) {
	if (top[i] == boundary[i]) {
		return stackEmpty(i);
	}
	else {
		printf("%s is popped from Stack No. %d\n", memory[top[i]].name, i);
		return memory[top[i]--];
	}
}

void printStack(int i) {
	int j = 0;
	for (j = top[i]; j > boundary[i]; --j) {
		printf("%s\n", memory[j].name);
	}
}
