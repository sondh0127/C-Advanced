#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "graph_weighted_jrb.h"

void show_int(int num)
{
	printf("%4d ", num);
}

int main(int argc, char const *argv[])
{

	Graph_W g = createGraph();
	// add the vertices and the edges of the graph here
	int s, t, length, path[1000];
	double weight = shortestPath(g, s, t, path, &length);
	if (weight == INFINITIVE_VALUE)
	   printf("No path between %d and %d\n", s, t);
	else {
	   printf("Path between %d and %d:", s, t);
	   for (int i=0; i< length; i++) printf("%4d", path[i]);
	   printf("Total weight: %f", weight);
	}

	return 0;
}