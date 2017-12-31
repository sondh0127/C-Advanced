#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "graph_weighted_jrb.h"
#include "../../lib/include/dllist.h"

void show_int(int num)
{
	printf("%4d ", num);
}
double shortestPath_T(Graph_W g, int s, int t, int * path, int * length);
// MAIN
int main(int argc, char const *argv[])
{

	Graph_W g = createGraph();
    addVertex(g, 0, "s");
    addVertex(g, 1, "t");
    addVertex(g, 2, "2");
    addVertex(g, 3, "3");
    addVertex(g, 4, "4");
    addVertex(g, 5, "5");
    addVertex(g, 6, "6");
    addVertex(g, 7, "7");
    addEdge(g, 0, 2, 9);
    addEdge(g, 0, 6, 14);
    addEdge(g, 0, 7, 15);
    addEdge(g, 2, 3, 24);
    addEdge(g, 3, 1, 19);
    addEdge(g, 3, 5, 2);
    addEdge(g, 4, 1, 6);
    addEdge(g, 4, 3, 6);
    addEdge(g, 5, 1, 16);
    addEdge(g, 5, 4, 11);
    addEdge(g, 6, 3, 18);
    addEdge(g, 6, 5, 30);
    addEdge(g, 6, 7, 5);
    addEdge(g, 7, 1, 44);
    addEdge(g, 7, 5, 20);

    int s = 0;
    int t = 1;
    int path[100];
    int length;
    double weight = shortestPath(g, s, t, path, &length);
    if (weight == INFINITIVE_VALUE) {
        printf("There is no path between %d and %d\n", s, t);
    } else {
        printf("Path between %d and %d: ", s, t);
        for (int i = 0; i < length; i++) {
            printf("%4d", path[i]);
        }
        printf("\nTotal weight: %.0f\n", weight);
    }

    dropGraph(g);
	return 0;
}