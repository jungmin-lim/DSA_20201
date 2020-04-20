#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polyNode *polyPointer;
typedef struct polyNode{
	int coef;
	int expon;
	polyPointer link;
}polyNode;

polyPointer addFront(int coef, int expon, polyPointer poly);
polyPointer addRear(int coef, int expon, polyPointer poly);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coef, int expon, polyPointer *rear);
void polyPrint(polyPointer poly);
polyPointer deleteAll(polyPointer poly);

int main(int argc, char *argv[]) {
	FILE *f;
	polyPointer polyA = NULL, polyB = NULL, polyC = NULL;
	char order;
	int coef, expon;

	f = fopen("a.txt", "r");
	fscanf(f, "%c", &order);
	if (order == 'a') {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			polyA = addFront(coef, expon, polyA);
		}
	}
	else {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			polyA = addRear(coef, expon, polyA);
		}
	}
	fclose(f);

	f = fopen("b.txt", "r");
	fscanf(f, "%c", &order);
	if (order == 'a') {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			polyB = addFront(coef, expon, polyB);
		}
	}
	else {
		while (fscanf(f, "%d %d", &coef, &expon) != EOF) {
			polyB = addRear(coef, expon, polyB);
		}
	}
	fclose(f);

	polyC = padd(polyA, polyB);

	printf("    a :\n");
	polyPrint(polyA);
	printf("\n");

	printf("    b :\n");
	polyPrint(polyB);
	printf("\n");

	printf("a+b=c :\n");
	polyPrint(polyC);
	printf("\n");

	polyA = deleteAll(polyA);
	polyB = deleteAll(polyB);
	polyC = deleteAll(polyC);
	return 0;
}

polyPointer addFront(int coef, int expon, polyPointer poly) {
	polyPointer newNode;
	if ((newNode = (polyPointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->link = poly;

	poly = newNode;
	return poly;
}

polyPointer addRear(int coef, int expon, polyPointer poly) {
	polyPointer newNode, temp, trail;
	if ((newNode = (polyPointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}
	
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->link = NULL;

	if (!poly) {
		return newNode;
	}

	temp = poly;
	trail = NULL;
	while (temp) {
		trail = temp;
		temp = temp->link;
	}
	
	trail->link = newNode;
	return poly;
}

polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum, comp;
	if ((rear = (polyPointer)malloc(sizeof(*rear))) == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}

	c = rear;
	while (a && b) {
		comp = a->expon - b->expon;
		if (comp < 0) {
			attach(b->coef, b->expon, &rear);
			b = b->link;
		}

		else if (comp == 0) {
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
		}

		else {
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}

	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	
	temp = c;
	c = c->link;
	free(temp);

	return c;
}

void attach(int coef, int expon, polyPointer *rear) {
	polyPointer newNode;
	if ((newNode = (polyPointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}

	newNode->coef = coef;
	newNode->expon = expon;
	(*rear)->link = newNode;
	(*rear) = newNode;

	return;
}

void polyPrint(polyPointer poly) {
	while (poly) {
		printf("(%p : %+4dx^%d : %p)\n", poly, poly->coef, poly->expon, poly->link);
		poly = poly->link;
	}

	return;
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
