#include <stdio.h>
#include <stdlib.h>

int maxIndex(int arr[], int size) {
	int max = 0, i;
	for (i = 0; i < size; ++i) {
		if (arr[max] < arr[i]) {
			max = i;
		}
	}
	return max;
}

int main(int argc, const char* argv[]) {
	char name[3][30], sex[3][30], element[10];
	int i, age[3];
	FILE* filepointer;
	filepointer = fopen("input.txt", "r");
	if (filepointer == NULL) {
		perror("Error opening file");
		return(-1);
	}

	for (i = 0; i < 3; ++i) {
		fscanf(filepointer, "%s %s %s", name[i], sex[i], element);
		age[i] = atoi(element);
	}

	i = maxIndex(age, 3);
	printf(" 이름\t성별\t나이\t\n");
	printf("============================\n");
	printf("%s\t %s\t %d\n", name[0], sex[0], age[0]);
	printf("%s\t %s\t %d\n", name[1], sex[1], age[1]);
	printf("%s\t %s\t %d\n", name[2], sex[2], age[2]);
	printf("============================\n\n");
	printf(" << 최고령 사용자 >> \n\n");
	printf(" %s\t %s\t %d\n", name[i], sex[i], age[i]);

	fclose(filepointer);
	return 0;
}
