#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
}node;

nodePointer initHead(nodePointer head);
void insertRear(nodePointer head, int data);
void printForward(nodePointer head);
void printBackward(nodePointer head);
void deleteFail(nodePointer head);
void deleteAll(nodePointer head);

int main(int argc, char *argv[]) {
	FILE *f;
	nodePointer header = NULL;
	int data;

	header = initHead(header);
	f = fopen("input.txt", "r");
	while (fscanf(f, "%d", &data) != EOF) {
		insertRear(header, data);
	}

	printf("After creating a doubly linked circular list with a head node :\n");
	printForward(header);
	printf("\n");
	printBackward(header);
	printf("\n");

	deleteFail(header);
	printf("\nAfter deleting numbers less than and equal to 50\n");
	printForward(header);
	printBackward(header);
	printf("\n");

	deleteAll(header);

	return 0;
}

nodePointer initHead(nodePointer head) {
	nodePointer newNode;
	if ((newNode = (nodePointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	newNode->llink = newNode;
	newNode->rlink = newNode;

	head = newNode;
	return head;
}

void insertRear(nodePointer head, int data) {
	nodePointer newNode;
	if ((newNode = (nodePointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insuffcient memory");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->llink = head->llink;
	newNode->rlink = head;

	head->llink->rlink = newNode;
	head->llink = newNode;

	return;
}

void printForward(nodePointer head) {
	nodePointer p = head->rlink;

	printf("forward\n");
	while (p != head) {
		printf("(%p %5d %p)   ", p->llink, p->data, p->rlink);
		p = p->rlink;
	}
	printf("\n");
	return;
}

void printBackward(nodePointer head) {
	nodePointer p = head->llink;

	printf("backward\n");
	while (p != head) {
		printf("(%p %5d %p)   ", p->llink, p->data, p->rlink);
		p = p->llink;
	}
	printf("\n");
	return;
}

void deleteFail(nodePointer head) {
	nodePointer p = head->rlink, q = head, deleteNode;

	while (p != head) {
		if (p->data <= 50) {
			deleteNode = p;

			p = deleteNode->rlink;
			p->llink = q;
			q->rlink = p;

			free(deleteNode);
		}
		else {
			q = p;
			p = p->rlink;
		}
	}
	return;
}

void deleteAll(nodePointer head) {
	nodePointer p = head->llink, q = head, deleteNode;

	while (p != head) {
		deleteNode = p;
		p = deleteNode->rlink;
		p->llink = q;
		q->rlink = p;

		free(deleteNode);
	}
	return;
}
