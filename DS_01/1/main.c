#include <stdio.h>

int sumAry1D_f1(int ary[], int size) {
	int sum = 0, i = 0;

	for (i = 0; i < size; ++i) {
		sum = sum + ary[i];
	}
	return sum;
}

int sumAry1D_f2(int *ary, int size) {
	int sum = 0, i = 0;

	for (i = 0; i < size; ++i) {
		sum = sum + ary[i];
	}
	return sum;
}

int sumAry1D_f3(int ary[6]) {
	int sum = 0, i = 0;
	
	for (i = 0; i < 6; ++i) {
		sum = sum + ary[i];
	}
	return sum;
}

int main(void) {
	int ary1D[] = { 1, 2, 3, 4, 5, 6 };
	int size = sizeof(ary1D) / sizeof(ary1D[0]);

	printf("sumAry1D_f1() %d \n", sumAry1D_f1(ary1D, size));
	printf("sumAry1D_f2() %d \n", sumAry1D_f2(ary1D, size));
	printf("sumAry1D_f3() %d \n", sumAry1D_f3(ary1D));

	return 0;
}