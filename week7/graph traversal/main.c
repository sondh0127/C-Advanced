#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"


void printVertex(int vertex) 
{
	printf("%2c ", vertex);
}

int main()
{
	Graph g = createGraph();

    addEdge(g, 'A', 'B');
    addEdge(g, 'A', 'S');
    addEdge(g, 'S', 'C');
    addEdge(g, 'S', 'G');
    addEdge(g, 'C', 'D');
    addEdge(g, 'C', 'E');
    addEdge(g, 'C', 'F');
    addEdge(g, 'E', 'H');
    addEdge(g, 'G', 'F');
    addEdge(g, 'G', 'H');
       
	
	// addEdge(g, 0, 1);
	// addEdge(g, 1, 2);
	// addEdge(g, 1, 3);
	// addEdge(g, 2, 3);
	// addEdge(g, 2, 4);
	// addEdge(g, 4, 5);


 //    printf("Graph:\n");
 //    printf("0__1__2__4__5\n");
 //    printf("   |  |\n");
 //    printf("   3__|\n");
 //    printf("\nBFS: start from node 1 to 4: \n");
	// BFS(g, 1, 4, printVertex);
	// printf("\nBFS: start from node 1 to all: \n");
	// BFS(g, 1, -1, printVertex);
	// printf("\nDFS: start from node 1 to 4: \n");
	// DFS(g, 1, 4, printVertex);
	// printf("\nDFS: start from node 1 to all: \n");
	// DFS(g, 1, -1, printVertex);

	printGraph(g, printVertex);
    printf("\nBFS: start from node 'A' to 'E':\n");
    BFS(g, 'A', 'E', printVertex);
    printf("\nBFS: start from node 'A' to all:\n");
    BFS(g, 'A', -1, printVertex);

    printf("\nDFS: start from node 'A' to 'E':\n");
    DFS(g, 'A', 'E', printVertex);
    printf("\nDFS: start from node 'A' to all:\n");
    DFS(g, 'A', -1, printVertex);

    printf("\n");
	return 0;
}
