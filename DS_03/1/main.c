#include <stdio.h>
#include <stdlib.h>
#define EXIT_FAILURE -1
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

int *make1dArray(int num) {
	int *array, i;
	MALLOC(array, sizeof(int) * num);

	for (i = 0; i < num; ++i) {
		array[i] = rand() % 100;
	}
	return array;
}

int main() {
	int *ipp;
	int i, num;
	printf("������ �迭�� ���� �Է� �ϼ��� : ");
	scanf("%d", &num);

	ipp = make1dArray(num);
	for (i = 0; i < num; ++i) {
		printf("ipp[%d] =%d ", i, ipp[i]);
	}
	printf("\n");
	return 0;
}