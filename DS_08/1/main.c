#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

void insert(listPointer *first, listPointer x, int dat);
listPointer insertSorted(listPointer head, int dat);
void delete(listPointer *first, listPointer trail, listPointer x);
listPointer deleteOdd(listPointer head);
listPointer deleteAll(listPointer head);
void printList(listPointer *linkedList);
void printData(listPointer head);

int main(int argc, char *argv[]) {
	FILE *f;
	listPointer linkedList = NULL, p, q;
	int dat;

	f = fopen("input.txt", "r");

	// insert sort
	while ((fscanf(f, "%d", &dat)) != EOF) {
		p = linkedList;
		q = linkedList;

		linkedList = insertSorted(linkedList, dat);
	}

	printf("The ordered list contains:\n");
	printData(linkedList);
	printf("\n\n");
	printf("After deleting nodes with odd values\n");
	linkedList = deleteOdd(linkedList);
	printf("\nThe ordered list contains:\n");
	printData(linkedList);

	linkedList = deleteAll(linkedList);
	fclose(f);
	return 0;
}

void insert(listPointer *first, listPointer x, int dat) {
	listPointer temp;
	if ((temp = (listPointer *)malloc(sizeof(*temp))) == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}
	temp->data = dat;

	if (*first == NULL) {
		temp->link = NULL;
		*first = temp;
	}
	else {
		if (x == NULL) {
			temp->link = *first;
			*first = temp;
		}
		else {
			temp->link = x->link;
			x->link = temp;
		}
	}
}

listPointer insertSorted(listPointer head, int dat) {
	listPointer p, q;

	p = head;
	q = NULL;

	while (p != NULL) {
		if (p->data > dat) {
			break;
		}
		q = p;
		p = p->link;
	}
	
	insert(&head, q, dat);
	return head;
}

void delete(listPointer *first, listPointer trail, listPointer x) {
	if (trail) {
		trail->link = x->link;
	}
	else {
		*first = (*first)->link;
	}
	free(x);
}

listPointer deleteOdd(listPointer head) {
	listPointer p, q, temp;
	p = head;
	q = NULL;

	while (p != NULL) {
		if ((p->data) % 2) {
			temp = p->link;
			delete(&head, q, p);
			p = temp;
		}
		else {
			q = p;
			p = p->link;
		}
	}
	return head;
}

listPointer deleteAll(listPointer head) {
	listPointer p, q;
	p = head;

	while (p != NULL) {
		head = head->link;
		free(p);
		p = head;
	}
	return head;
}

void printList(listPointer *linkedList) {
	printf("Linked List contains: ");
	while (*linkedList) {
		printf("%4d ", (*linkedList)->data);
		(*linkedList) = (*linkedList)->link;
	}
}

void printData(listPointer head) {
	listPointer p;
	p = head;
	while (p != NULL) {
		printf("(%p, %4d, %p )", p, p->data, p->link);
		p = p->link;
	}
}