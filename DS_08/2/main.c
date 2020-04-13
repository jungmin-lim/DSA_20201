#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
	int data;
	struct listNode *link;
}listNode;

void insert(listNode **first, listNode *x, int dat);
listNode *insertSorted(listNode *head, int dat);
void delete(listNode **first, listNode *trail, listNode *x);
listNode *deleteOdd(listNode *head);
void printList(listNode *linkedList);
void printData(listNode *head);

int main(int argc, char *argv[]) {
	FILE *f;
	listNode *linkedList = NULL;
	int dat;

	f = fopen("input.txt", "r");
	while ((fscanf(f, "%d", &dat)) != EOF) {
		linkedList = insertSorted(linkedList, dat);
	}

	printf("The ordered list contains:\n");
	printData(linkedList);
	printf("\n\n");

	printf("After deleting nodes with odd values\n");
	linkedList = deleteOdd(linkedList);
	printf("\nThe ordered list contains:\n");
	printData(linkedList);

	fclose(f);
	return 0;
}

void insert(listNode **first, listNode *x, int dat) {
	listNode *temp;
	if ((temp = (listNode *)malloc(sizeof(*temp))) == NULL) {
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
			temp->link = NULL;
			*first = temp;
		}
		else {
			temp->link = x->link;
			x->link = temp;
		}
	}
}

listNode *insertSorted(listNode *head, int dat) {
	listNode *p, *q, *node;

	if ((node = (listNode *)malloc(sizeof(*node))) == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}
	node->data = dat;
	
	p = head;
	q = head;

	while (p != NULL) {
		if (p->data > dat) {
			break;
		}
		q = p;
		p = p->link;
	}
	
	if (p == head) {
		node->link = head;
		head = node;
	}
	else {
		node->link = p;
		q->link = node;
	}
	return head;
}

void delete(listNode **first, listNode *trail, listNode *x) {
	if (trail) {
		trail->link = x->link;
	}
	else {
		*first = (*first)->link;
	}
	free(x);
}

listNode *deleteOdd(listNode *head) {
	listNode *p, *q;
	p = head;
	q = head;

	while (p != NULL) {
		if ((p->data) % 2) {
			if (p == head) {
				head = head->link;
				free(p);
				p = head;
				q = head;
			}
			else {
				q->link = p->link;
				free(p);
				p = q->link;
			}
		}
		else {
			q = p;
			p = p->link;
		}
	}
	return head;
}

void printList(listNode *linkedList) {
	listNode *p;
	p = linkedList;
	printf("Linked List contains: ");
	while (p) {
		printf("%4d ", p->data);
		p = p->link;
	}
}

void printData(listNode *head) {
	listNode *p;
	p = head;
	while (p != NULL) {
		printf("(%p, %4d, %p )", p, p->data, p->link);
		p = p->link;
	}
}