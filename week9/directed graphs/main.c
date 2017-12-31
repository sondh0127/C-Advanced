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
	addVertex(G, 1, "A1");
	addVertex(G, 2, "A2");
	addVertex(G, 3, "A3");
	addVertex(G, 4, "A4");
	addVertex(G, 5, "A5");
	addVertex(G, 6, "A6");
	addVertex(G, 7, "A7");

	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 5);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 4, 6);
	addEdge(G, 5, 6);
	addEdge(G, 6, 7);
	printf("================\n");
	printGraph(G);
	if (isCycle(G) == 1) {
		printf("Can not make topological sort\n");
		return 1;
	}
	int n;
	int output2[10];
	printf("The topological order:\n");
	topologicalSort_T(G, output2, &n);
	for (int i = 0; i < n; ++i)
	{
		show_int(output2[i]);
	}

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
	
	printf("\n");

	// if(isCycle(G) == 1) 
	// printf("\nHave a cycles in the graph\n");
	// else {
	// 	printf("\nGraph is DAG graph!\n");
	// 	topologicalSort(G, show_int);
	// 	printf("\n");
	// }

	return 0;
}