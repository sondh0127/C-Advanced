	#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H
#include "../../lib/include/jrb.h"
typedef struct {
	JRB edges;
	JRB vertices; 
} Graph_D;

Graph_D createGraph();
void dropGraph(Graph_D graph);

void addVertex(Graph_D graph, int id, char *name);
char *getVertex(Graph_D graph, int id);
int isAdjacent(Graph_D graph, int v1, int v2);
void addEdge(Graph_D graph, int v1, int v2);

int outDegree(Graph_D graph, int v, int *output);
int inDegree(Graph_D graph, int v, int* output);

void BFS(Graph_D graph,int start,int stop,void(*func)(int));
void DFS(Graph_D graph, int start, int stop, void (*func)(int));

int isCycleVertex(Graph_D graph, int start);
int isCycle(Graph_D graph);

void showVertices(Graph_D graph);
void printGraph(Graph_D graph);
void topologicalSort(Graph_D graph, void (*visit)(int));

void topologicalSort_T(Graph_D g, int * output, int * n);
#endif /* GRAPH_JRB_H */
