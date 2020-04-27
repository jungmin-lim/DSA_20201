#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode *treePointer;
typedef struct queuenode *queuePointer;
typedef struct treenode {
	char data;
	treePointer leftChild, rightChild;
}treenode;
typedef struct queuenode {
	treePointer node;
	queuePointer link;
}queuenode;

void enqueue(queuePointer *head, treePointer node);
void dequeue(queuePointer *head);
void insertTree(treePointer *root, queuePointer *head, char data);
void inorder(treePointer root);
void preorder(treePointer root);
void postorder(treePointer root);

int main(int argc, char *argv[]){
	FILE *f;
	queuePointer queue = NULL;
	treePointer root = NULL;
	char data;

	f = fopen("input.txt", "r");
	while (fscanf(f, "%c", &data) != EOF) {
		insertTree(&root, &queue, data);
	}

	printf("creating a complete bianry tree\n\n");
	printf("thee bianry tree traversals\n");

	printf("inorder traversal	:");
	inorder(root);
	printf("\npreorder traversal	:");
	preorder(root);
	printf("\npostorder traversal	:");
	postorder(root);
	printf("\n");

	return 0;
}

void enqueue(queuePointer *head, treePointer node) {
	queuePointer newQueuenode, p;
	if ((newQueuenode = malloc(sizeof(*newQueuenode))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	newQueuenode->node = node;
	newQueuenode->link = NULL;

	if (!(*head)) {
		(*head) = newQueuenode;
	}
	else {
		p = *head;
		while ((p->link) != NULL) {
			p = p->link;
		}
		p->link = newQueuenode;
	}

	return;
}

void dequeue(queuePointer *head) {
	queuePointer temp;
	temp = *head;
	(*head) = (*head)->link;

	free(temp);
	return;
}

void insertTree(treePointer *root, queuePointer *head, char data) {
	treePointer newTreenode, temp;
	if ((newTreenode = malloc(sizeof(*newTreenode))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	newTreenode->data = data;
	newTreenode->leftChild = NULL; newTreenode->rightChild = NULL;

	if (!(*root)) {
		(*root) = newTreenode;
	}
	else {
		temp = (*head)->node;
		if (!(temp->leftChild)) {
			temp->leftChild = newTreenode;
		}
		else if (!(temp->rightChild)) {
			temp->rightChild = newTreenode;
			dequeue(head);
		}
	}
	enqueue(head, newTreenode);

	return;
}

void inorder(treePointer root) {
	if (root) {
		inorder(root->leftChild);
		printf("%c", root->data);
		inorder(root->rightChild);
	}
}

void preorder(treePointer root) {
	if (root) {
		printf("%c", root->data);
		preorder(root->leftChild);
		preorder(root->rightChild);
	}
}

void postorder(treePointer root) {
	if (root) {
		postorder(root->leftChild);
		postorder(root->rightChild);
		printf("%c", root->data);
	}
}