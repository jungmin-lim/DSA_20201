#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

void insertLast(listPointer *last, listPointer node);
void deleteOdd(listPointer *last);
void deleteAll(listPointer *last);
void printList(listPointer last);
int length(listPointer last);

int main(int argc, char *argv[]) {
	FILE *f;
	listPointer linkedList = NULL, newNode;
	int dat;

	f = fopen("input.txt", "r");

	// insert sort
	while ((fscanf(f, "%d", &dat)) != EOF) {
		if ((newNode = (listPointer)malloc(sizeof(*newNode))) == NULL) {
			fprintf(stderr, "Insufficient Memroy");
			exit(EXIT_FAILURE);
		}
		newNode->data = dat;
		insertLast(&linkedList, newNode);
	}

	printf("The Circularly list contains:\n");
	printList(linkedList);
	printf("\n\n");

	printf("After deleting nodes with odd values\n\n");
	deleteOdd(&linkedList);
	printf("The Circularly list contains:\n");
	printList(linkedList);

	printf("\n");
	deleteAll(&linkedList);

	fclose(f);
	return 0;
}


void insertLast(listPointer *last, listPointer node) {
	if (!(*last)) {
		*last = node;
		node->link = node;
	}
	else {
		node->link = (*last)->link;
		(*last)->link = node;
		(*last) = node;
	}
}

void deleteOdd(listPointer *last) {
	listPointer p, q;
	q = (*last);

	if (*last) {
		p = (*last)->link;
		while (p != (*last)) {
			if ((p->data) % 2) {
				q->link = p->link;
				free(p);
				p = q->link;
			}
			else {
				q = p;
				p = p->link;
			}
		}
		if ((p->data) % 2) {
			if (p->link == p) {
				free(p);
				(*last) = NULL;
			}
			else{
				q->link = p->link;
				(*last) = q;
				free(p);
			}

		}
	}
}

void deleteAll(listPointer *last) {
	listPointer p;

	if (*last) {
		p = (*last)->link;
		while (p != (*last)) {
			(*last)->link = p->link;
			free(p);
			p = (*last)->link;
		}
		free(p);
		(*last) = NULL;
	}
}

void printList(listPointer last) {
	listPointer temp;
	if (last) {
		temp = last->link;
		while (temp != last) {
			printf("(%p, %5d, %p )", temp, temp->data, temp->link);
			temp = temp->link;
		}
		printf("(%p, %5d, %p )", temp, temp->data, temp->link);
	}
}

int length(listPointer last) {
	listPointer temp;
	int count = 0;
	if (last) {
		temp = last;
		do {
			count++;
			temp = temp->link;
		} while (temp != last);
	}
	return count;
}
