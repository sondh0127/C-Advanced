#include <stdio.h>
#include <stdlib.h>

#include "graph_matrix.h"


Graph createGraph(int size_max)
{
	Graph g;
	g.size_max = size_max;
	g.matrix = (int*)malloc(size_max * size_max* sizeof(int));
	if(g.matrix == NULL) {
		fprintf(stderr, "ERROR: Not enough memory space to create graph!\n");
		EXIT_FAILURE;
	}
	return g;
}

void addEdge(Graph g, int vertex_i, int vertex_j)
{
	if(vertex_i > g.size_max || vertex_j > g.size_max) {
		fprintf(stderr, "ERROR: value vertex_i or vertex_j over size_max\n");
		return;
	}
	

	/* matrix[j][i] */
	g.matrix[vertex_i * g.size_max + vertex_j] = 1;
	/* matrix[i][j] */
	g.matrix[vertex_j * g.size_max + vertex_i] = 1;
    
}

int isAdjacent(Graph g, int vertex_i, int vertex_j)
{
    if(g.matrix[vertex_i * g.size_max + vertex_j] == 1) return 1;
	if(g.matrix[vertex_j * g.size_max + vertex_i] == 1 ) return 1;
	return 0;
}

int getAdjacentVertices(Graph g, int vertex, int *output)
{
	
	int count = 0;
	for (int i = 0; i < g.size_max; i++) {
		if(isAdjacent(g, vertex, i)) {
			output[count++] = i;
		}
	}

	return count;
}

void dropGraph(Graph *g)
{
    free((*g).matrix);
	(*g).size_max = 0;
}

void printGraph(Graph g)
{
	printf("Size of graph: %d\n", g.size_max);
    for (int i = 0; i < g.size_max; i++) {
		for (int j = 0; j < g.size_max; j++) {
			printf("%2d ", g.matrix[j*g.size_max + i]);
		}
		printf("\n");
    }
}

