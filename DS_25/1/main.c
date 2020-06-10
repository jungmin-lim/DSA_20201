#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1000
#define MAX_STRING 10
#define BUCKET 11
#define SLOT 1

typedef struct element {
	char item[MAX_STRING];
	int key;
}element;

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

element *search(element *hash[], int key) {
	int homeBucket, currentBucket;

	homeBucket = hashFunction(key);
	for (currentBucket = homeBucket; hash[currentBucket] && hash[currentBucket]->key != key;) {
		currentBucket = (currentBucket + 1) % BUCKET;
		if (currentBucket == homeBucket) return NULL;
	}
	if(hash[currentBucket] && hash[currentBucket]->key == key && strcmp())
}

int main(int argc, char *argv[]) {
	FILE *fp;
	element *hash[BUCKET], data;
	char str[BUF_SIZE], tok[2] = ' ';
	char *token;

	init(hash);

	fp = fopen("input.txt", "r");
	fgets(str, BUF_SIZE, fp);
	
	token = strtok(str, tok);
	while (token != NULL) {
		strcpy(data.item, token);
		data.key = stringToInt(data.item);
		insert(hash, data);

		token = strtok(NULL, str);
	}



	fclose(fp);
	return 0;
}
