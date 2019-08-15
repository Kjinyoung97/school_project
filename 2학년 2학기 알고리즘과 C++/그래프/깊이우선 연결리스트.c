#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

void graph_init(GraphType *g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType *g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점의 개수 초과\n");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g, int u, int v) {
	GraphNode *node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = u;
	node->link = g->adj_list[v];
	g->adj_list[v] = node;
}

int visited[MAX_VERTICES];

void dfs_list(GraphType *g, int v) {
	GraphNode *w;
	visited[v] = TRUE;
	printf("%d\n", v);
	for (w = g->adj_list[v]; w; w = w->link)
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
}

main() {
	int i;
	GraphType g;

	graph_init(&g);
	for (i = 0; i < 5; i++)
		insert_vertex(&g, i);
	insert_edge(&g, 3,2);
	insert_edge(&g, 2,3);
	insert_edge(&g, 3,4);
	insert_edge(&g, 4,3);
	insert_edge(&g, 4,0);
	insert_edge(&g, 0,4);
	insert_edge(&g, 4, 2);
	insert_edge(&g, 2, 4);
	insert_edge(&g, 2,1);
	insert_edge(&g, 1,2);
	insert_edge(&g, 2,0);
	insert_edge(&g, 0,2);
	insert_edge(&g, 1, 0);
	insert_edge(&g, 0, 1);
	dfs_list(&g, 3);
}