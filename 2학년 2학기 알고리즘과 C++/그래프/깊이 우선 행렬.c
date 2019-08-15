#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50


typedef struct GraphType {
	int n;
	int *adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void graph_init(GraphType *g) {
	int r;
	int c = 0;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType *g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점의 개수 초과\n");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

int visited[MAX_VERTICES];

void dfs_mat(GraphType *g, int v) {
	int w;
	visited[v] = TRUE;
	printf("%d\n", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
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
	dfs_mat(&g, 3);
}