#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void stackEmpty(void);
void stackFull(void);
void push(int item);
precedence pop(void);
precedence getToken(char *symbol, int *n);
void postfix(FILE *f);
void printToken(precedence token, FILE *f);

int main(void) {
	FILE *f;
	f = fopen("input.txt", "r");
	fscanf(f, "%s", expr);
	fclose(f);

	f = fopen("output.txt", "w");
	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>\n");
	printf("infix expression\t: %s\n", expr);
	printf("postfix expression \t: ");
	postfix(f);
	fclose(f);
	return 0;
}

void stackEmpty(void) {
	fprintf(stderr, "Stack is empty, cannot delete element\n");
	exit(EXIT_FAILURE);
}

void stackFull(void) {
	fprintf(stderr, "Stack is full, cannot add element\n");
	exit(EXIT_FAILURE);
}

void push(int item) {
	if (top >= MAX_STACK_SIZE-1) {
		stackFull();
	}
	stack[++top] = item;
}

precedence pop(void) {
	if (top == -1) {
		stackEmpty();
	}
	return stack[top--];
}

precedence getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
		case '(': return lparen;
		case ')': return rparen;
		case '+': return plus;
		case '-': return minus;
		case '/': return divide;
		case '*': return times;
		case '%': return mod;
		case '\0': return eos;
		default: return operand;
	}
}

void postfix(FILE *f) {
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {

		if (token == operand) {
			printf("%c", symbol);
			fprintf(f, "%c", symbol);
		}

		else if(token == rparen){
			while (stack[top] != lparen) {
				printToken(pop(), f);
			}
			pop();
		}

		else{
			while (isp[stack[top]] >= icp[token]) {
				printToken(pop(), f);
			}
			push(token);
		}
	}

	while ((token = pop()) != eos) {
		printToken(token, f);
	}
	printf("\n");
}

void printToken(precedence token, FILE *f) {
	switch (token) {
		case plus: printf("+"); fprintf(f, "+");
			break;
		case minus: printf("-"); fprintf(f, "-");
			break;
		case divide: printf("/"); fprintf(f, "/");
			break;
		case times: printf("*"); fprintf(f, "*");
			break;
		case mod: printf("\%"); fprintf(f, "\%");
			break;
	}
}