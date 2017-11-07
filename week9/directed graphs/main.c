#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "graph_direct_jrb.h"

void show_int(int num)
{
	printf("%4d ", num);
}

int main(int argc, char const *argv[])
{

	Graph_D G = createGraph();

	addVertex(G, 0, "V0");
	addVertex(G, 1, "V1");
	addVertex(G, 2, "V2");
	addVertex(G, 3, "V3");
	addVertex(G, 4, "V4");

	addEdge(G, 0, 1);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 1, 3);
	addEdge(G, 3, 4);
	printf("================\n");
	printGraph(G);
	// int count = inDegree(G, 1, output);
	// printf("\nInDegree\n");
	// for (int i = 0; i < count; ++i)	{
	// 	printf("%d ",output[i]);
	// }
	// int output2[10];
	// int count2 = outDegree(G, 1, output2);
	// printf("\nOutDegree\n");
	// for (int i = 0; i < count2; ++i){
	// 	printf("%d ",output2[i]);
	// }
	
	// printf("\n");
	

	if(isCycle(G) == 1) 
	printf("\nHave a cycles in the graph\n");
	else {
		printf("\nGraph is DAG graph!\n");
		topologicalSort(G, show_int);
		printf("\n");
	}
	


	return 0;
}