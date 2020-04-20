#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct polyNode *polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;

polyPointer avail = NULL;
void addFront(int coef, int expon, polyPointer poly);
void addRear(int coef, int expon, polyPointer poly);
polyPointer getNode(void);
void retNode(polyPointer node);
void cerase(polyPointer *poly);
void attach(int coef, int expon, polyPointer *rear);
polyPointer cpadd(polyPointer a, polyPointer b);
void polyPrint(polyPointer poly);
void availPrint(polyPointer poly);
polyPointer deleteAll(polyPointer poly);

int main(int argc, char *argv[]) {
	FILE *f;
	polyPointer polyA = NULL, polyB = NULL, polyC = NULL;
	char order;
	int coef, expon;

	// poly init
	polyA = getNode();
	polyA->expon = -1;
	polyA->link = polyA;
	polyB = getNode();
	polyB->expon = -1;
	polyB->link = polyB;
	polyC = getNode();
	polyC->expon = -1;
	polyC->link = polyC;

	// input value
	f = fopen("a.txt", "r");
	fscanf(f, "%c", &order);
	if (order == 'a') {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			addFront(coef, expon, polyA);
		}
	}
	else {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			addRear(coef, expon, polyA);
		}
	}
	fclose(f);

	f = fopen("b.txt", "r");
	fscanf(f, "%c", &order);
	if (order == 'a') {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			addFront(coef, expon, polyB);
		}
	}
	else {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			addRear(coef, expon, polyB);
		}
	}
	fclose(f);

	polyC = cpadd(polyA, polyB);

	printf("    a :\n");
	polyPrint(polyA);
	printf("\n");

	printf("    b :\n");
	polyPrint(polyB);
	printf("\n");

	printf("a+b=c :\n");
	polyPrint(polyC);
	printf("\n");

	cerase(&polyA);
	cerase(&polyB);
	cerase(&polyC);

	printf("avail :\n");
	availPrint(avail);
	printf("\n");

	avail = deleteAll(avail);
	return 0;
}

void addFront(int coef, int expon, polyPointer poly) {
	polyPointer newNode;

	newNode = getNode();
	newNode->coef = coef;
	newNode->expon = expon;

	newNode->link = poly->link;
	poly->link = newNode;
}

void addRear(int coef, int expon, polyPointer poly) {
	polyPointer newNode, temp, trail;

	newNode = getNode();
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->link = poly;


	temp = poly->link;
	trail = poly;
	while (temp != poly) {
		trail = temp;
		temp = temp->link;
	}
	
	trail->link = newNode;
}

polyPointer getNode(void) {
	polyPointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else {
		if ((node = (polyPointer)malloc(sizeof(*node))) == NULL) {
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}
	}
	return node;
}

void retNode(polyPointer node) {
	node->link = avail;
	avail = node;
}

void cerase(polyPointer *poly) {
	polyPointer temp;
	if (*poly) {
		temp = (*poly)->link;
		(*poly)->link = avail;
		avail = temp;
		*poly = NULL;
	}
}

void attach(int coef, int expon, polyPointer *rear) {
	polyPointer temp;
	temp = getNode();

	temp->coef = coef;
	temp->expon = expon;
	(*rear)->link = temp;
	(*rear) = temp;
}

polyPointer cpadd(polyPointer a, polyPointer b) {
	polyPointer startA, c, lastC;
	int sum, comp, done = FALSE;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1;
	lastC = c;

	do {
		comp = a->expon - b->expon;
		if (comp < 0) {
			attach(b->coef, b->expon, &lastC);
			b = b->link;
		}

		else if (comp == 0) {
			if (startA == a) done = TRUE;
			else {
				sum = a->coef + b->coef;
				if (sum) {
					attach(sum, a->expon, &lastC);
				}
				a = a->link;
				b = b->link;
			}
		}

		else {
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	} while (!done);
	lastC->link = c;
	return c;
}

void polyPrint(polyPointer poly) {
	polyPointer temp = poly;
	do {
		printf("(%p : %+4dx^%d : %p)\n", temp , temp->coef, temp->expon, temp->link);
		temp = temp->link;
	} while (temp != poly);

	return;
}

void availPrint(polyPointer poly) {
	while (poly) {
		printf("(%p : %+4dx^%d : %p)\n", poly, poly->coef, poly->expon, poly->link);
		poly = poly->link;
	}
}

polyPointer deleteAll(polyPointer poly) {
	polyPointer temp;
	while (poly) {
		temp = poly;
		poly = poly->link;
		free(temp);
	}

	return poly;
}
