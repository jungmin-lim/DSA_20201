#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET 8
#define SLOT 1

int count = 0;

void init_rand(int data[]) {
	int i;
	data[0] = 0;
	for (i = 1; i < BUCKET; i++) {
		data[i] = (rand() % (BUCKET - 1)) + 1;
	}
	return;
}

int hashFunction(int item) {
	return item % BUCKET;
}

int random_probing(int hash[], int rand_data[], int item) {
	int i, key = hashFunction(item);
	for (i = 0; i < BUCKET; i++) {
		count++;
		if (hash[hashFunction(key + rand_data[i])] == item) return hashFunction(key + rand_data[i]);
	}
	return -1;
}

int main() {
	FILE* fp; 
	int hash[BUCKET], data[100], rand_data[BUCKET], seed, size;
	int key, buck, search;
	int i = 0;

	for (i = 0; i < BUCKET; ++i) {
		hash[i] = -1;
	}

	fp = fopen("input.txt", "r");

	printf("key sequence from file :");
	i = 0;
	while (fscanf(fp, "%d", &data[i]) != EOF) {
		fprintf(stdout, "%5d", data[i++]);
	}
	size = i;

	printf("\ninput seed >> ");

	scanf("%d", &seed);
	srand(seed);

	init_rand(rand_data);
	printf("\n");

	for(i = 0; i < size; ++i) {
		key = hashFunction(data[i]);
		buck = 0;
		while (hash[hashFunction(key + rand_data[buck])] != -1) {
			buck++;
			if (buck == BUCKET) {
				fprintf(stderr, "hash overflow\n");
				exit(EXIT_FAILURE);
			}
		}
		hash[hashFunction(key + rand_data[buck])] = data[i];
	}

	for (int i = 1; i < BUCKET; i++) {
		fprintf(stdout, "randNum[%d] : %3d\n", i, rand_data[i]);
	}

	fprintf(stdout, "\n\t   key\n");
	for (int i = 0; i < BUCKET; i++) {
		if (hash[i] < 0) {
			fprintf(stdout, "ht[%2d] : \n", i);
		}
		else fprintf(stdout, "ht[%2d] : %4d\n", i, hash[i]);
	}
	printf("\n\n");

	while (1) {
		fprintf(stdout, "input 0 to quit\n");
		fprintf(stdout, "key to search >> ");

		scanf("%d", &search);
		if (search == 0) break;

		count = 0;
		key = random_probing(hash, rand_data, search);
		
		if(key == -1) printf("it doesn't exist!\n\n");
		else printf("key : %d, the number of comparisions : %d\n\n", search, count);
	}

	fclose(fp);
	return 0;
}