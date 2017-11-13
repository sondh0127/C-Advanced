	#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H
#include "../../lib/include/jrb.h"
typedef struct {
	JRB edges;
	JRB vertices; 
} Graph_W;
#define INFINITIVE_VALUE 10000000

Graph_W createGraph();
void dropGraph(Graph_W graph);

void addVertex(Graph_W graph, int id, char *name);
char *getVertex(Graph_W graph, int id);
int isAdjacent(Graph_W graph, int v1, int v2);
// ==============Add modifier============
void addEdge(Graph_W graph, int v1, int v2, double weight);
double getEdgeValue(Graph_W graph, int v1, int v2);
int getHighestID(Graph_W graph);
double shortestPath(Graph_W graph,int start,int stop, int *output_path, int *length);

int outDegree(Graph_W graph, int v, int *output);
int inDegree(Graph_W graph, int v, int* output);

void BFS(Graph_W graph,int start,int stop,void(*func)(int));
void DFS(Graph_W graph, int start, int stop, void (*func)(int));

int isCycleVertex(Graph_W graph, int start);
int isCycle(Graph_W graph);

void showVertices(Graph_W graph);
void printGraph(Graph_W graph);
void topologicalSort(Graph_W graph, void (*visit)(int));

void topologicalSort_T(Graph_W g, int * output, int * n);
#endif /* GRAPH_JRB_H */
