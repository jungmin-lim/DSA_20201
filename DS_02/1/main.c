#include <stdio.h>
#include <stdlib.h>
#define EXIT_FAILURE -1

int *func1() {
	int *npNum;
	if ((npNum = (int *)malloc(sizeof(int))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}

	*npNum = 10;
	return npNum;
}

void func2(int *pNum) {
	*pNum = 100;
}

void func3(int **ppNum) {
	**ppNum = 200;
}
int main(void) {
	int *pNum;
	pNum = func1();
	printf("%d\n", *pNum);


	func2(pNum);
	printf("%d\n", *pNum);

	func3(&pNum);
	printf("%d\n", *pNum);

	return 0;
}