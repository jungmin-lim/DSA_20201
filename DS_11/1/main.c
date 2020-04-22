#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 24
#define TRUE 1
#define FALSE 0

typedef struct node *nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

nodePointer top = NULL;

void push(int dat);
int pop();
void initSeq(nodePointer seq[], int n);
void insertFront(nodePointer seq[], int p1, int p2);
void printSeq(nodePointer seq[], int n);
void printEquiv(nodePointer seq[], int n);

int main(int argc, char argv[]) {
	nodePointer seq[MAX_SIZE];
	int i, j, n, p1, p2;
	FILE *f;

	f = fopen("input.txt", "r");
	fscanf(f, "%d", &n);

	printf("/* MAX_SZIE of a set S: %d */\n", MAX_SIZE);
	printf("current size of S : %d\n", n);
	printf("S = { ");
	for (i = 0; i < n; ++i) printf("%d ", i);
	printf("}\n");
	initSeq(seq, n);

	printf("input pairs : ");
	while (fscanf(f, "%d %d", &p1, &p2) != EOF) {
		printf("%dR%d ", p1, p2);
		insertFront(seq, p1, p2);
	}
	printf("\n\n");

	printSeq(seq, n);
	printEquiv(seq, n);
	return 0;
}

void push(int dat) {
	nodePointer newNode;
	if ((newNode = (nodePointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient Error");
		exit(EXIT_FAILURE);
	}

	newNode->data = dat;
	newNode->link = top;

	top = newNode;
	return;
}

int pop(void) {
	nodePointer p;
	int dat;
	p = top;
	top = top->link;

	dat = p->data;
	free(p);

	return dat;
}

void initSeq(nodePointer seq[], int n) {
	int i;
	for (i = 0; i < n; ++i) {
		if ((seq[i] = (nodePointer)malloc(sizeof(*seq[i]))) == NULL) {
			fprintf(stderr, "Insufficient Memory");
			exit(EXIT_FAILURE);
		}
		seq[i]->link = NULL;
	}

	return;
}

void insertFront(nodePointer seq[], int p1, int p2) {
	nodePointer newNode1, newNode2;
	if ((newNode1 = (nodePointer)malloc(sizeof(*newNode1))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	if ((newNode2 = (nodePointer)malloc(sizeof(*newNode2))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}

	newNode1->data = p2;
	newNode2->data = p1;

	newNode1->link = seq[p1]->link;
	newNode2->link = seq[p2]->link;

	seq[p1]->link = newNode1;
	seq[p2]->link = newNode2;

	return;
}

void printSeq(nodePointer seq[], int n) {
	int i;
	nodePointer p;
	printf("symmetric 관계 linked List\n");
	for (i = 0; i < n; ++i) {
		printf("%d : symmetric 관계:\n", i);
		p = seq[i]->link;
		while (p) {
			printf("(%p %d %p) ", p, p->data, p->link);
			p = p->link;
		}
		printf("\n");
	}
}

void printEquiv(nodePointer seq[], int n) {
	nodePointer p;
	int i, temp, out[MAX_SIZE];
	for (i = 0; i < n; ++i) {
		out[i] = TRUE;
	}

	for (i = 0; i < n; ++i) {
		if (out[i]) {
			printf("\nNew class: %d", i);
			out[i] = FALSE;
			p = seq[i]->link;

			while (1) {
				while (p) {
					temp = p->data;
					if (out[temp]) {
						printf("%5d", temp);
						out[temp] = FALSE;

						push(temp);
						p = p->link;
					}
					else {
						p = p->link;
					}
				}

				if (top == NULL) break;
				p = seq[pop()]->link;
			}
		}
	}
	
	return;
}