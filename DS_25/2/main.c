#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET 8
#define SLOT 1

int count = 0;

void init_rand(int data[]) {
	int i;
	for (i = 1; i < BUCKET; i++) {
		data[i] = (rand() % (BUCKET - 1)) + 1;
		if ((flag & (1 << data)) > 0) {
			i--;
			continue;
		}
		else {
			randNum[i] = data;
			flag = flag | (1 << data);
		}
	}
}

int hash(int item) {
	return item % b;
}

int random_probing(int item) {
	int key = hash(item);
	for (int i = 0; i < b; i++) {
		compare_count++;
		if (ht[hash(key + randNum[i])] == item) return hash(key + randNum[i]);
	}
	return -1;
}

int main() {
	FILE* fp; 
	int data[100], rand_data[BUCKET], seed, size;
	int i = 0;

	fp = fopen("input.txt", "r");

	printf("key sequence from file :");

	// input data from file
	while (fscanf(fp, "%d", &data[i]) != EOF) {
		fprintf(stdout, "%5d", data[i++]);
	}
	size = i - 1;

	printf("\ninput seed >> ");

	scanf("%d", &seed);
	srand(seed);

	init_rand(rand_data);

	printf("\n");

	// make hash table
	iter = 0;
	while (tempArr[iter] != -999) {
		key = hash(tempArr[iter]);
		cur = 0;
		while (ht[hash(key + randNum[cur])] != 0) {
			cur++;
			if (cur == b) {
				printf("\n==== Overflow!! ====\n");
				exit(EXIT_FAILURE);
			}
		}
		ht[hash(key + randNum[cur])] = tempArr[iter];
		iter++;
	}

	// print data
	for (int i = 1; i < b; i++) {
		printf("randNum[%d] : %3d\n", i, randNum[i]);
	}

	printf("\n\t   key\n");
	for (int i = 0; i < b; i++) {
		printf("ht[%2d] : %4d\n", i, ht[i]);
	}
	printf("\n\n");

	// search data
	while (1) {
		printf("input 0 to quit\nkey to search >> ");
		scanf("%d", &buf);
		if (buf == 0) break;
		compare_count = 0;
		key = random_probing(buf);
		
		if(key == -1) printf("it doesn't exist!\n\n");
		else printf("key : %d, the number of comparisions : %d\n\n", buf, compare_count);
	}
}