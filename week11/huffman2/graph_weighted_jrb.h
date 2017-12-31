#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H
#include "../../lib/include/jrb.h"

typedef struct {
	JRB vertices; 
	JRB edges;
} Graph_W;

#define INFINITIVE_VALUE 10000000

Graph_W createGraph();
void addVertex(Graph_W graph, int id, char *name);
char *getVertexName(Graph_W graph, int id);

// addition function
int isAdjacent(Graph_W graph, int v1, int v2);

void addEdge(Graph_W graph, int v1, int v2, double weight);
double getEdgeValue(Graph_W graph, int v1, int v2);

void dropGraph(Graph_W graph);

int outDegree(Graph_W graph, int v, int *outDegreeList);
int inDegree(Graph_W graph, int v, int *inDegreeList);

double shortestPath(Graph_W graph, int start, int stop, int *outputPath, int *length);

// bonus function
int getHighestID(Graph_W graph);
#endif /* WEIGHTED_GRAPH_H */