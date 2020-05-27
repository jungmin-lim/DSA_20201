#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTEX 100

typedef struct node {
	int count;
	struct node* link;
}element;

void topSort(element *graph[], int n);

int main(int argc, char *argv[]) {
	FILE *f;
	element *graph[MAX_VERTEX], *temp, *newNode;
	int vertex, edge = 0;
	int from, to;
	int i, j;

	f = fopen("input.txt", "r");
	fscanf(f, "%d", &vertex);
	for (i = 0; i < vertex; ++i) {
		if ((graph[i] = (element *)malloc(sizeof(*graph[i]))) == NULL) {
			fprintf(stderr, "Insufficient Memory");
			exit(EXIT_FAILURE);
		}
		graph[i]->count = 0;
		graph[i]->link = NULL;
	}

	while (fscanf(f, "%d %d", &from, &to) != EOF) {
		edge++;
		temp = graph[from];
		while (temp->link != NULL) {
			temp = temp->link;
		}

		if ((newNode = (element *)malloc(sizeof(*newNode))) == NULL) {
			fprintf(stderr, "Insufficient Memory");
			exit(EXIT_FAILURE);
		}
		newNode->count = to;
		newNode->link = NULL;

		temp->link = newNode;
		graph[to]->count++;
	}

	topSort(graph, vertex);
	fclose(f);
	return 0;
}

void topSort(element *graph[], int n) {
	int i, j, k, top = -1;
	element *temp;

	for (i = 0; i < n; ++i) {
		if (!graph[i]->count) {
			graph[i]->count = top;
			top = i;
		}
	}
	for (i = 0; i < n-1; ++i) {
		if (top == -1) {
			fprintf(stderr, "\nNetwork has a cycle. Sort terminated\n");
			exit(EXIT_FAILURE);
		}
		else {
			j = top;
			top = graph[top]->count;
			fprintf(stdout, "%d -> ", j);
			for (temp = graph[j]->link; temp; temp = temp->link) {
				k = temp->count;
				graph[k]->count--;
				if (!graph[k]->count) {
					graph[k]->count = top;
					top = k;
				}
			}
		}
	}
	for (i; i < n; ++i) {
		if (top == -1) {
			fprintf(stderr, "\nNetwork has a cycle. Sort terminated\n");
			exit(EXIT_FAILURE);
		}
		else {
			j = top;
			top = graph[top]->count;
			fprintf(stdout, "%d\n", j);
			for (temp = graph[j]->link; temp; temp = temp->link) {
				k = temp->count;
				graph[k]->count--;
				if (!graph[k]->count) {
					graph[k]->count = top;
					top = k;
				}
			}
		}
	}
}