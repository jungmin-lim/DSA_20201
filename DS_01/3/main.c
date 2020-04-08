#include <stdio.h>
#define EXIT_FAILURE -1

int main(void) {
	int i, *pi;
	float f, *pf;
	if (!(pi = malloc(sizeof(int))) ||
		!(pf = malloc(sizeof(float)))) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}

	*pi = 1024;
	*pf = 3.14;
	printf("an integer = %d, a float = %f\n", *pi, *pf);
	free(pi);
	free(pf);

	return 0;
}