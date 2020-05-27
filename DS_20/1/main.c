#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 200
#define MAX_VERTEX 1000

typedef struct {
	int key;
	int u;
	int v;
} element;

element heap[MAX_ELEMENTS];
int n = 0, ans = 0;
int vertex = -1, edge;
int parent[MAX_VERTEX];

typedef struct node {
	int data;
	struct node* link;
} node;

node** graph;

void insertEdge(int v1, int v2);
void add(element item);
element delete();
int find(int i);
void set_union(int i, int j);
void kruskal(int n);

int main(int argc, char *argv[]) {
	FILE *f;
	element item;
	f = fopen("input.txt", "r");

	fscanf(f, "%d", &edge);

	for (int i = 0; i < edge; ++i) {
		fscanf(f, "%d %d %d", &item.u, &item.v, &item.key);
		vertex = max(vertex, item.u);
		vertex = max(vertex, item.v);
		add(item);
	}

	graph = (node**)malloc(sizeof(node*) * (vertex + 1));
	for (int i = 0; i < vertex + 1; i++) {
		graph[i] = NULL;
	}

	kruskal(vertex + 1);

	printf("\n최소비용 : %d\n", ans);

	fclose(f);
	return 0;
}

void insertEdge(int v1, int v2) {
	node* temp = (node*)malloc(sizeof(node));
	temp->data = v2;
	temp->link = graph[v1];
	graph[v1] = temp;
}

void add(element item) {
	if (n == MAX_ELEMENTS - 1) {
		printf("Heap FULL!\n");
		exit(EXIT_FAILURE);
	}

	int i = ++n;
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element delete() {
	int parent, child;
	element item, temp;
	if (n == 0) {
		printf("The heap is empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[n--];

	parent = 1;
	child = 2;
	while (child <= n) {
		if ((child < n) && (heap[child].key > heap[child + 1].key))
			child++;

		if (temp.key <= heap[child].key)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

int find(int i) {
	for (; parent[i] >= 0; i = parent[i]);
	return i;
}

void set_union(int i, int j) {
	parent[i] = j;
}

void kruskal(int n) {
	int edge_accepted = 0;
	int uset, vset;
	element e;

	memset(parent, -1, sizeof(parent));
	while (edge_accepted < (n - 1)) {
		e = delete();

		uset = find(e.u);
		vset = find(e.v);
		if (uset != vset) {
			printf("(%d, %d) %d\n", e.u, e.v, e.key);
			ans += e.key;
			edge_accepted++;
			set_union(uset, vset);
		}
	}
}