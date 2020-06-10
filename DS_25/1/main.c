#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 11
#define BUCKET 11
#define SLOT 1

typedef struct element {
	char item[MAX_STRING];
	int key;
}element;

int count = 1;

int stringToInt(char *key) {
	int number = 0;
	while (*key) {
		number += *key++;
	}
	return number;
}

int hashFunction(int key) {
	return key % BUCKET;
}

element *search(element *hash[], char data[]) {
	int homeBucket, currentBucket;
	int key = stringToInt(data);
	homeBucket = hashFunction(key);

	for (currentBucket = homeBucket; hash[currentBucket] && hash[currentBucket]->key != key;) {
		count++;
		currentBucket = (currentBucket + 1) % BUCKET;
		if (currentBucket == homeBucket) return NULL;
	}

	if (hash[currentBucket] && hash[currentBucket]->key == key && strcmp(hash[currentBucket]->item, data) == 0) return hash[currentBucket];
	return NULL;
}

int main() {
	FILE *fp;
	element *hash[BUCKET], *data;
	char str[MAX_STRING];
	int buck, i;

	for (i = 0; i < BUCKET; ++i) {
		hash[i] = NULL;
	}

	fp= fopen("input.txt", "r");

	fprintf(stdout, "input strings : ");
	while (fscanf(fp, "%s", str) != EOF) {
		if ((data = (element *)malloc(sizeof(*data))) == NULL) {
			fprintf(stderr, "Insufficient Memory\n");
			exit(EXIT_FAILURE);
		}

		strcpy(data->item, str);
		data->key = stringToInt(data->item);

		buck = hashFunction(data->key);
		while (hash[buck] != NULL) {
			buck = (++buck) % 11;
		}
		hash[buck] = data;

		fprintf(stdout, "%s ", str);
	}
	fprintf(stdout, "\n\t      item    key\n");

	for (i = 0; i < BUCKET; ++i) {
		fprintf(stdout, "ht[%2d] :", i);
		if (hash[i] == NULL) {
			fprintf(stdout, "\n");
		}
		else {
			fprintf(stdout, "%10s%7d\n", hash[i]->item, hash[i]->key);
		}
	}

	printf("\nstring to search >> ");
	scanf("%s", str);

	data = search(hash, str);
	if (!data) {
		printf("it doesn't exist!\n");
	}
	else {
		printf("item: %s, key : %d, the number of comparisions : %d", data->item, data->key, count);
	}
}
