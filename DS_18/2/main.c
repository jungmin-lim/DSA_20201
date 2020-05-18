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
typedef struct queue *queuePointer;
typedef struct queue {
	int data;
	queuePointer next;
};

void addFront(linkedPointer *head, int data);
void printList(linkedPointer head);
void enqueue(queuePointer *queue, int data);
int dequeue(queuePointer *queue);
void bfs(int vertex, linkedPointer adList[]);

int main(int argc, char *argv[]) {
	FILE *f;
	linkedPointer adList[MAX_VERTEX] = { NULL };
	int vertex, edge;
	int a, b, i, j;

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
		fprintf(stdout, "\n");
	}

	fprintf(stdout, "<<<<<<<<<<<<< Breath First Search >>>>>>>>>>>>>\n");
	for (i = 0; i < vertex; ++i) {
		fprintf(stdout, "bfs<%d> :", i);
		bfs(i, adList);
		fprintf(stdout, "\n");
		for (j = 0; j < vertex; ++j) {
			visited[j] = FALSE;
		}
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

void enqueue(queuePointer *queue, int data) {
	queuePointer newQueuenode, p = (*queue);
	if ((newQueuenode = (queuePointer)malloc(sizeof(*newQueuenode))) == NULL) {
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	newQueuenode->data = data;
	if (!(*queue)) {
		newQueuenode->next= newQueuenode;
		(*queue) = newQueuenode;
		return;
	}

	while(p->next != (*queue)){
		p = p->next;
	}

	p->next= newQueuenode;
	newQueuenode->next= (*queue);
	return;
}

int dequeue(queuePointer *queue) {
	queuePointer p, q;
	int ret;
	if (!(*queue)) {
		return NULL;
	}

	p = (*queue);
	q = (*queue);
	while (q->next != (*queue)) {
		q = q->next;
	}

	(*queue) = (*queue)->next;
	if (p == (*queue)) {
		(*queue) = NULL;
	}
	else {
		q->next = (*queue);
	}

	ret = p->data;
	free(p);
	return ret;
}

void bfs(int vertex, linkedPointer adList[]) {
	linkedPointer w;
	queuePointer front = NULL, rear = NULL;

	visited[vertex] = TRUE;
	printf("%5d", vertex);

	enqueue(&front, vertex);
	while (front) {
		vertex = dequeue(&front);
		for (w = adList[vertex]; w; w = w->next) {
			if (!visited[w->data]) {
				printf("%5d", w->data);
				enqueue(&front, w->data);
				visited[w->data] = TRUE;
			}
		}
	}
}