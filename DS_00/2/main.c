#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {

	int array1[10] = { 0 }, array2[10] = { 0 }, i;
	char element[10];
	FILE* filepointer1, * filepointer2;
	filepointer1 = fopen("input-1.txt", "r");
	if (filepointer1 == NULL) {
		perror("Error opening file");
		return(-1);
	}
	filepointer2 = fopen("input-2.txt", "r");
	if (filepointer2 == NULL) {
		perror("Error opening file");
		return(-1);
	}

	for(i = 0; i < 10; ++i) {
		fscanf(filepointer1, "%s", element);
		array1[i] = atoi(element);
	}

	for(i = 0; i < 10; ++i) {
		fscanf(filepointer2, "%s", element);
		array2[i] = atoi(element);

	}

	for (i = 0; i < 10; ++i) {
		printf("%3d, ", array1[i]);
	}
	printf("\n");

	for (i = 0; i < 10; ++i) {
		printf("%3d, ", array2[i]);
	}
	printf("\n");

	for (i = 0; i < 10; ++i) {
		printf("%3d, ", array1[i] + array2[i]);
	}
	printf("\n");

	fclose(filepointer1);
	fclose(filepointer2);

	return 0;
}