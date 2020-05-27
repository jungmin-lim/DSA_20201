#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTEX 200
#define TRUE 1
#define FALSE 0
#define INF 10000

typedef struct {
	int key;
	int u;
	int v;
} element;

int n = 0, vertex = -1, edge, ans;
int weight[MAX_VERTEX][MAX_VERTEX];
int selected[MAX_VERTEX];
int dist[MAX_VERTEX];

int get_min_vertex(int n);
void prim(int s, int n);

int main() {
	element item;
	FILE* f = fopen("input.txt", "r");
	if (f == NULL) {
		printf("File Error!\n");
		exit(EXIT_FAILURE);
	}

	fscanf(f, "%d", &edge);
	for (int i = 0; i < MAX_VERTEX; i++) {
		for (int j = 0; j < MAX_VERTEX; j++)
			weight[i][j] = INF;
	}

	for (int i = 0; i < edge; i++) {
		fscanf(f, "%d %d %d", &item.u, &item.v, &item.key);
		weight[item.u][item.v] = item.key;
		weight[item.v][item.u] = item.key;
		vertex = max(vertex, item.u);
		vertex = max(vertex,item.v);
	}

	prim(0, vertex + 1);

	for (int i = 0; i < vertex + 1; i++) {
		ans += dist[i];
	}
	printf("최소 비용 : %d\n", ans);
	fclose(f);
}

int get_min_vertex(int n) {
	int v = -1, i;
	for (i = 0; i < n; i++) 
		if (!selected[i]) { v = i; break; }

	for (i = 0; i < n; i++) 
		if (!selected[i] && (dist[i] < dist[v])) v = i;

	return v;
}

void prim(int s, int n) {
	int u, v;
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	dist[s] = 0;
	for (int i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
		}

		printf("선택 vertex : %d,   distance : ", u);

		for (int j = 0; j < n; j++) {
			if (dist[j] == INF) 
				printf("  INF");
			
			else
				printf("%5d", dist[j]);
		}
		printf("\n");
	}
}

