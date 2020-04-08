#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101
#define COMPARE(x, y) (((x) < (y))? -1 : ((x) == (y))? 0 : 1))

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

void polyAdd(polynomial poly1, polynomial poly2, polynomial *polyResult) {
	int i, hDegree;
	if (poly1.degree > poly2.degree) {
		hDegree = 1;
		polyResult->degree = poly1.degree;
	}
	else {
		hDegree = 2;
		polyResult->degree = poly2.degree;
	}

	if (hDegree == 1) {
		for (i = poly1.degree; i > poly2.degree; --i) {
			polyResult->coef[i] = poly1.coef[i];
		}
	}
	else {
		for (i = poly2.degree; i > poly1.degree; --i) {
			polyResult->coef[i] = poly2.coef[i];
		}
	}

	for (i = poly1.degree; i >= 0; --i) {
		polyResult->coef[i] = poly1.coef[i] + poly2.coef[i];
	}
	return;
}

void polyPrint(polynomial *poly) {
	int i;
	for (i = poly->degree; i > 0; i--) {
		printf("%.1fx^%d + ", poly->coef[i], i);
	}
	printf("%.1f\n", poly->coef[0]);
	return;
}

int main(void) {

	int i, a, b;
	polynomial polyA, polyB, *polyC;
	polyC = (polynomial *)malloc(sizeof(polynomial));
	printf("<< C(x) = A(x) + B(x) >>\n");
	printf("Input the degree of items of A(x) : ");
	scanf("%d", &polyA.degree);
	printf("Input the coefficients A(x) : ");
	for (i = (polyA.degree); i >= 0; --i) {
		scanf("%f", &polyA.coef[i]);
	}
	printf("Input the degree of items of B(x) : ");
	scanf("%d", &polyB.degree);
	printf("Input the coefficients B(x) : ");
	for (i = (polyB.degree); i >= 0; --i) {
		scanf("%f", &polyB.coef[i]);
	}
	polyAdd(polyA, polyB, polyC);
	printf("A(X) = ");
	polyPrint(&polyA);
	printf("B(X) = ");
	polyPrint(&polyB);
	printf("C(X) = ");
	polyPrint(polyC);

	return 0;
}