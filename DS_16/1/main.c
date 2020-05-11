#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500

typedef int iType;
typedef struct {
	int key;
	iType item;
}element;

typedef struct node *treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
}treeNode;

element *search(treePointer root, int k);
treePointer modifiedSearch(treePointer root, int k);
int insert(treePointer *node, int k, iType item);
void inorder(treePointer root);

int main(int argc, char *argv[]) {
	int i, n, k, seed, random;
	treePointer root = NULL;

	fprintf(stdout, "random number generation (1 ~ %d)\n", MAX_SIZE);
	fprintf(stdout, "%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf("%d", &n);
	fprintf(stdout, "%s", "seed : ");
	scanf("%u", &seed);

	fprintf(stdout, "\ncreating a BST from random numbers\n");
	srand(seed);

	for (i = 0; i < n; ++i) {
		while (1) {
			random = rand() % MAX_SIZE;
			if (insert(&root, random, random)) {
				fprintf(stdout, "%4d", random);
				break;
			}
		}
	}

	fprintf(stdout, "\nthe key to search : ");
	scanf("%d", &k);
	fprintf(stdout, "the search process : ");
	if (search(root, k)) {
		fprintf(stdout, "\nthe element is in BST\n");
	}
	else {
		fprintf(stdout, "\nthe element is not in BTS\n");
	}

	fprintf(stdout, "\ninorder traversal of the BST shows the sorted sequence\n");
	inorder(root);

	return 0;
}

element *search(treePointer root, int k) {
	if (!root) {
		return NULL;
	}

	fprintf(stdout, "%d => ", root->data.key);
	if (k == root->data.key) {
		return &(root->data);
	}
	if (k < root->data.key) {
		return search(root->leftChild, k);
	}
	return search(root->rightChild, k);
}

treePointer modifiedSearch(treePointer root, int k) {
	treePointer temp = root;
	while (root) {
		if (k == root->data.key) return NULL;
		if (k < root->data.key) {
			temp = root;
			root = root->leftChild;
		}
		else {
			temp = root;
			root = root->rightChild;
		}
	}
	return temp;
}

int insert(treePointer *node, int k, iType item) {
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		if ((ptr = malloc(sizeof(*ptr))) == NULL) {
			fprintf(stderr, "Insufficient memory");
		}
		ptr->data.key = k;
		ptr->data.item = item;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node) {
			if (k < temp->data.key) temp->leftChild = ptr;
			else temp->rightChild = ptr;
		}
		else {
			*node = ptr;
		}
		return 1;
	}
	else {
		return 0;
	}
}

void inorder(treePointer root) {
	if (root) {
		inorder(root->leftChild);
		fprintf(stdout, "%4d", root->data.key);
		inorder(root->rightChild);
	}
}