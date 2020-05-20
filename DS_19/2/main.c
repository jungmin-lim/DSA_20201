#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 1024
#define TRUE 1
#define FALSE 0

short int visited[MAX_VERTEX];

typedef struct linkedNode *linkedPointer;
typedef struct linkedNode {
	int data;
	linkedPointer next;
}linkedNode;

void addFront(linkedPointer *head, int data);
void printList(linkedPointer head);
void dfs(int vertex);

int main(int argc, char *argv[]) {
	FILE *f;
	linkedPointer adList[MAX_VERTEX] = { NULL };
	int vertex, edge;
	int a, b, i, j = 1;

	f = fopen("input.txt", "r");
	fscanf(f, "%d %d", &vertex, &edge);
	
	for (i = 0; i < edge; i++) {
		fscanf(f, "%d %d", &a, &b);

		addFront(&adList[a], b);
		addFront(&adList[b], a);
	}


	fprintf(stdout, "<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
	for (i = 0; i < vertex; ++i) {
		fprintf(stdout, "graph[%d] :", i);
		printList(adList[i]);
		fprintf(stdout, "\n\n");
	}

	fprintf(stdout, "<<<<<<<<<<<<< Connected Components >>>>>>>>>>>>>\n");
	for (i = 0; i < vertex; ++i) {
		if (visited[i]) continue;
		fprintf(stdout, "connected componet %d :", j++);
		dfs(i, adList);
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

void dfs(int vertex, linkedPointer adList[]) {
	linkedPointer w;
	visited[vertex] = TRUE;
	printf("%5d", vertex);
	for (w = adList[vertex]; w; w = w->next) {
		if (!visited[w->data]) {
			dfs(w->data, adList);
		}
	}
}