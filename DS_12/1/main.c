#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}node;

void init(treePointer root);
void inorder(treePointer node);
void preorder(treePointer node);
void postorder(treePointer node);

int main(int argc, char *argv[]) {
	treePointer root;
	if ((root = (treePointer)malloc(sizeof(*root))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	root->data = 'A';
	printf("creating a binary tree\n");
	init(root);
	printf("\n");

	printf("three binary tree traversals\n");

	printf("indorder traversal	:\n");
	inorder(root);

	printf("preorder traversal	:\n");
	preorder(root);

	printf("postorder traversal	:\n");
	postorder(root);
	return 0;
}

void init(treePointer root) {
	treePointer treeB, treeC, treeD, treeE;
	if ((treeB = malloc(sizeof(*treeB))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	if ((treeC = malloc(sizeof(*treeC))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	if ((treeD = malloc(sizeof(*treeD))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	if ((treeE = malloc(sizeof(*treeE))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}

	treeB->data = 'B'; treeC->data = 'C'; treeD->data = 'D'; treeE->data = 'E';

	root->leftChild = treeB; root->rightChild = treeC;
	treeB->leftChild = treeD; treeB->rightChild = treeE;
	treeC->leftChild = NULL; treeC->rightChild = NULL;
	treeD->leftChild = NULL; treeD->rightChild = NULL;
	treeE->leftChild = NULL; treeE->rightChild = NULL;

	return;
}

void inorder(treePointer node) {
	if (node) {
		inorder(node->leftChild);
		printf("(%p : %p %c %p)\n", node, node->leftChild, node->data, node->rightChild);
		inorder(node->rightChild);
	}
}

void preorder(treePointer node) {
	if (node) {
		printf("(%p : %p %c %p)\n", node, node->leftChild, node->data, node->rightChild);
		preorder(node->leftChild);
		preorder(node->rightChild);
	}
}

void postorder(treePointer node) {
	if (node) {
		postorder(node->leftChild);
		postorder(node->rightChild);
		printf("(%p : %p %c %p)\n", node, node->leftChild, node->data, node->rightChild);
	}
}