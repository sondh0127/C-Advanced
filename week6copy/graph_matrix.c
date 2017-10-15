#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph_matrix.h"


graph create_graph(int size_max){
	graph ret;
     
	ret.size_max = size_max;
	ret.matrix = (int*)malloc(sizeof(int) * (size_max));
	if(ret.matrix == NULL) {
		exit(1);
	}
	return ret;
}

void add_edge(graph g, int v1, int v2) {
	if(v1 > g.size_max || v2 > g.size_max) 
	{
		fprintf(stderr, "ERROR: value v1 or v2 over size_max");
		return;
	}
	g.matrix[v1 * g.size_max + v2] = 1;
    g.matrix[v2 * g.size_max + v1] = 1;
}

int isAdjacent(graph g, int v1, int v2) {
    int * matrix = g.matrix;
    if (matrix[v1 * g.size_max + v2] == 1) return 1;
    return 0;
}

int getAdjacentVertices(graph g, int vertex, int * output) {
    int * matrix = g.matrix;
    int i;
    int count = 0;
    for (i = 0; i < g.size_max; i++) {
        if (matrix[i * g.size_max + vertex] == 1) {
            output[count] = i;
            count++;
        }
    }
    return count;
}

void printGraph(graph g) {
    int * matrix = g.matrix;
    int sizemax = g.size_max;
    int size = sqrt(sizemax);
    int i;
    for (i = 0; i < sizemax; i++) {
        printf("%d ", matrix[i]);
        if ((i + 1)%size == 0) printf("\n");
    }
}

void dropGraph(graph g) {
    free(g.matrix);
    g.size_max = 0;
}
