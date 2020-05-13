#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 1024

typedef struct edge *edgePointer;
typedef struct edge{
	int leftVertex;
	int rightVertex;
	edgePointer left;
	edgePointer right;
}edge;

void makeMultiGraph(edgePointer adList[], FILE *f);
void printMultiGraph(edgePointer adList[], int source, int order);

int main(int argc, char *argv[]) {
	FILE *f;
	edgePointer adList[MAX_VERTEX] = { NULL };
	int vertex, edge;
	int a, b, i;

	f = fopen("input.txt", "r");
	fscanf(f, "%d %d", &vertex, &edge);

	makeMultiGraph(adList, f);
	fprintf(stdout, "<<<<<<<<<<<<< edges incident to each vertex >>>>>>>>>>>>>\n");
	fprintf(stdout, "\n간선의 정점 출력 순서 - 입력데이터 순서대로\n");
	for (i = 0; i < vertex; ++i) {
		fprintf(stdout, "edges incident to vertex %d : ", i);
		printMultiGraph(adList, i, 1);
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게\n");
	for (i = 0; i < vertex; ++i) {
		fprintf(stdout, "edges incident to vertex %d : ", i);
		printMultiGraph(adList, i, 0);
		fprintf(stdout, "\n");
	}

	fclose(f);
	return 0;
}

void makeMultiGraph(edgePointer adList[], FILE *f) {
	edgePointer newEdge, temp = NULL, temp1 = NULL;
	int i = 0, source, dest;

	while ((fscanf(f, "%d %d", &source, &dest)) != EOF) {
		if ((newEdge = (edgePointer)malloc(sizeof(*newEdge))) == NULL) {
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}

		newEdge->leftVertex = source;
		newEdge->rightVertex = dest;
		newEdge->left = NULL;
		newEdge->right = NULL;

		if (adList[source] == NULL) {
			adList[source] = newEdge;
		}
		else {
			temp = adList[source];
			while (temp != NULL) {
				temp1 = temp;
				if (temp->leftVertex == source) {
				temp = temp->left;
				}
				else {
				temp = temp->right;
				}
			}
				
			if (temp1->leftVertex == source) {
				temp1->left = newEdge;
			}
			else {
				temp1->right = newEdge;
			}
		}

		if (adList[dest] == NULL) {
			adList[dest] = newEdge;
		}
		else {
			temp = adList[dest];
			while (temp != NULL) {
				temp1 = temp;
				if (temp->leftVertex == dest) {
					temp = temp->left;
				}
				else {
					temp = temp->right;
				}
			}
				
			if (temp1->leftVertex == dest) {
				temp1->left = newEdge;
			}
			else {
				temp1->right = newEdge;
			}
		}
	}
	return ;
}


void printMultiGraph(edgePointer adList[], int source, int order) {
	edgePointer temp = adList[source];
	if (order) {
		while (temp != NULL) {
			fprintf(stdout, "(%d, %d) ", temp->leftVertex, temp->rightVertex);
			if (temp->leftVertex == source) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
	}
	else {
		while (temp != NULL) {
			if (temp->leftVertex == source) {
				fprintf(stdout, "(%d, %d) ", temp->leftVertex, temp->rightVertex);
				temp = temp->left;
			}
			else {
				fprintf(stdout, "(%d, %d) ", temp->rightVertex, temp->leftVertex);
				temp = temp->right;
			}
		}
	}
	return;
}
