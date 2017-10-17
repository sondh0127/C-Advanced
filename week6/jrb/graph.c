#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"


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
	
	Graph_JRB  g = createGraph_JRB();
	addEdge(g, 0, 1);
	addEdge(g, 0, 2);
	addEdge(g, 1, 2);
	addEdge(g, 1, 3);
	
	printGraph_JRB(g);
	n = getAdjacentVertices(g, 1, output);
	if(n == 0)
		printf("No adjacent vertices of node 1 \n");
	else {
		printf("Adjacent vertices of node 1: \n");
		for(i = 0; i < n; i++)
			printf("%2d ", output[i]);
	}
	
	printf("\n== Test ==\n");
	dropGraph_JRB(g);
	printGraph_JRB(g);
	return 0;
}
