#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTEX 100
#define INF 999

typedef struct node{
	int vertex;
	struct node* next;
}element;

int weight[MAX_VERTEX][MAX_VERTEX];
int distance[MAX_VERTEX];
int found[MAX_VERTEX];
int path[MAX_VERTEX];

void shortestPath(int v, int cost[][MAX_VERTEX], int distance[], int n, int found[]);
int choose(int distance[], int n, int found[]);
void printPath(int v, int distance[]);

int main(int argc, char *argv[]) {
	FILE *f;

	int vertex, edge;
	int from, to;
	int i, j;

	f = fopen("input.txt", "r");
	fscanf(f, "%d %d", &vertex, &edge);

	for (i = 0; i < vertex; ++i) {
		for (j = 0; j < vertex; ++j) {
			weight[i][j] = INF;
		}
	}
	for (i = 0; i < edge; ++i) {
		fscanf(f, "%d %d", &from, &to);
		fscanf(f, "%d", &weight[from][to]);
		weight[to][from] = weight[from][to];
	}
	
	
	shortestPath(0, weight, distance, vertex, found);
	fprintf(stdout, "\n");

	for (i = 1; i < vertex; ++i) {
		printPath(i, distance);
	}
	fclose(f);

	return 0;
}

void shortestPath(int v, int cost[][MAX_VERTEX], int distance[], int n, int found[]) {
	int i, u, w;
	for (i = 0; i < n; ++i) {
		found[i] = FALSE;
		distance[i] = cost[v][i];
	}

	found[v] = TRUE;
	distance[v] = 0;
	path[v] = 0;
	fprintf(stdout, "%d : ", v);
	for (w = 0; w < n; ++w) {
		fprintf(stdout, "%5d", distance[w]);
	}
	fprintf(stdout, "\n");

	for (i = 0; i < n - 2; ++i) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; ++w) {
			if (!found[w]) {
				if (distance[u] + cost[u][w] < distance[w]) {
					distance[w] = distance[u] + cost[u][w];
					path[w] = u;
				}
			}
		}
		fprintf(stdout, "%d : ", u);
		for (w = 0; w < n; ++w) {
			fprintf(stdout, "%5d", distance[w]);
		}
		fprintf(stdout, "\n");
	}
}

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INF;
	minpos = -1;
	for (i = 0; i < n; ++i) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void printPath(int v, int distance[]) {
	int current = v, previous = 0;
	int stack[MAX_VERTEX], top = -1;

	fprintf(stdout, "distance[0-%d]=%d \t: ", v, distance[v]);

	while (current != 0) {
		stack[++top] = current;
		current = path[current];
	}

	while (top != -1) {
		current = stack[top--];
		fprintf(stdout, "<%d-%d> ", previous, current);
		previous = current;
	}

	fprintf(stdout, "\n");
}