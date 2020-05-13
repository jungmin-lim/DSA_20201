#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 1024

typedef struct linkedNode *linkedPointer;
typedef struct linkedNode {
	int data;
	linkedPointer next;
}linkedNode;

void addFront(linkedPointer *head, int data);
void printList(linkedPointer head);

int main(int argc, char *argv[]) {
	FILE *f;
	linkedPointer adList[MAX_VERTEX] = { NULL };
	char directed;
	int vertex, edge;
	int a, b, i;

	f = fopen("input.txt", "r");
	fscanf(f, "%c %d %d", &directed, &vertex, &edge);
	
	for (i = 0; i < edge; i++) {
		fscanf(f, "%d %d", &a, &b);

		addFront(&adList[a], b);
		if (directed == 'u') {
			addFront(&adList[b], a);
		}
	}


	fprintf(stdout, "<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
	for (i = 0; i < vertex; ++i) {
		fprintf(stdout, "adjList[%d] :", i);
		printList(adList[i]);
		fprintf(stdout, "\n");
	}
	fclose(f);
	return 0;
}

void addFront(linkedPointer *head, int data) {
	linkedPointer newNode;
	if ((newNode = (linkedPointer)malloc(sizeof(*newNode))) == NULL) {
		fprintf(stderr, "Insufficient Memory");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->next = *head;

	*head = newNode;
	return;
}

void printList(linkedPointer head) {
	while (head != NULL) {
		fprintf(stdout, "%5d", head->data);
		head = head->next;
	}
	return;
}