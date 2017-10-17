#include <stdio.h>
#include <stdlib.h>
#include "graph_matrix.h"
#include <string.h>


void initOutput(int *output, int size)
{
	for(int i = 0 ; i< size; i++) {
		output[i] = - 1;
	}
}

int main()
{
	int i, n ,output[100];
	initOutput(output, 100);
	
	Graph g = createGraph(5);
	addEdge(g, 0, 1);
	addEdge(g, 0, 2);
	addEdge(g, 1, 2);
	addEdge(g, 1, 3);
	
	printGraph(g);
	n = getAdjacentVertices(g, 1, output);
	if(n == 0)
		printf("No adjacent vertices of node 1 \n");
	else {
		printf("Adjacent vertices of node 1: \n");
		for(i = 0; i < n; i++)
			printf("%2d ", output[i]);
	}
	
	printf("\n== Test ==\n");
	dropGraph(&g);
	printGraph(g);
	
	return 0;
}
