#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *matrix;
	int size_max;
} Graph;

extern Graph createGraph(int size_max);
extern void addEdge(Graph g, int vertex_i, int vertex_j);
extern int isAdjacent(Graph g, int vertex_i, int vertex_j);
extern int getAdjacentVertices(Graph g, int vertex, int *output);
extern void dropGraph(Graph *g);

void printGraph(Graph g);

#endif /* GRAPH_MATRIX_H */

