#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H
#include "../../lib/include/jrb.h"
typedef JRB Graph;

Graph createGraph();
void addEdge(Graph g, int v1, int v2);
int isAdjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int vertex, int *output);

void printGraph(Graph g, void (*func)(int));
void dropGraph(Graph g);
// Traversal

void BFS(Graph g, int start, int stop, void(*func)(int));
void DFS(Graph g, int start, int stop, void(*func)(int));
#endif /* GRAPH_JRB_H */
