#include <stdio.h>

int main(int argc, const char* argv[]) {
	int var1, var2;
	printf("두개의 정수 입력 >> ");
	scanf_s("%d %d", &var1, &var2);
	printf("두수의 덧셈 결과 : %d\n", var1 + var2);
	printf("두수의 곱셈 결과 : %d\n", var1 * var2);

	return 0;
}
