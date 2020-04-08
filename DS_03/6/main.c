#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define EXIT_FAILURE -1
#define COMPARE(x, y) (((x) < (y))? -1 : ((x) == (y))? 0 : 1)

typedef struct {
	float coef;
	int expon;
}term;

int avail = 0;
term terms[MAX_TERMS];

void attach(float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) {
	float coefficient;
	*startD = avail;
	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
			case -1:
				attach(terms[startB].coef, terms[startB].expon);
				startB++;
				break;
			case 0:
				coefficient = terms[startA].coef + terms[startB].coef;
				if (coefficient) {
					attach(coefficient, terms[startA].expon);
				}
				startA = startA + 1;
				startB = startB + 1;
				break;
			case 1:
				attach(terms[startA].coef, terms[startA].expon);
				startA++;
		}
	}
	for (; startA <= finishA; startA++) {
		attach(terms[startA].coef, terms[startA].expon);
	}
	for (; startB <= finishB; startB++) {
		attach(terms[startB].coef, terms[startB].expon);
	}
	*finishD = avail - 1;
	
}

void pPrint(int start, int finish) {
	
	int i;
	for (i = start; i < finish; ++i) {
		printf("%.1fx^%d + ", terms[i].coef, terms[i].expon);
	}
	printf("%.1fx^%d\n", terms[i].coef, terms[i].expon);
}

int main(void) {
	int a, b, i;
	int startA, finishA, startB, finishB, startD, finishD;

	printf("<< D(x) = A(x) + B(x) >>\n");
	printf("Input the number of items of A(x) : ");
	scanf("%d", &a);
	printf("Input the number of items of B(x) : ");
	scanf("%d", &b);
	avail = a + b;
	printf("\nInput in descending order\n\n");
	printf("coefficient and exponent of A(x) : ");
	for (i = 0; i < a; ++i) {
		scanf("%f %d,", &terms[i].coef, &terms[i].expon);
	}
	printf("coefficient and exponent of B(x) : ");
	for (i = a; i < a+b; ++i) {
		scanf("%f %d,", &terms[i].coef, &terms[i].expon);
	}
	padd(0, a - 1, a, a + b - 1, &startD, &finishD);
	printf("\n\n");
	printf("A(x) = ");
	pPrint(0, a - 1);
	printf("B(x) = ");
	pPrint(a,a+b-1);
	printf("D(x) = ");
	pPrint(startD, finishD);
}