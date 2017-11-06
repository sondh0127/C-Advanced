#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "graph_direct_jrb.h"

int main(int argc, char const *argv[])
{
	Graph_D G = createGraph();

	addVertex(G, 0, "V0");
	addVertex(G, 1, "V1");
	addVertex(G, 2, "V2");
	addVertex(G, 3, "V3");

	addEdge(G, 0, 1);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 1, 3);
	addEdge(G, 3, 4);
	printf("TEST\n");
	if(isDAG(G) == 1) 
		printf("The Graph is acycle\n");
	else
		printf("Have a cycles in the graph\n");


	return 0;
}