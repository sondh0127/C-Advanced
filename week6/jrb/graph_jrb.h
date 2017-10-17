#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H
#include "../../lib/libfdr/jrb.h"
typedef JRB Graph_JRB;

Graph_JRB createGraph_JRB();
void addEdge(Graph_JRB g, int vertex_i, int vertex_j);
int isAdjacent(Graph_JRB g, int vertex_i, int vertex_j);
int getAdjacentVertices(Graph_JRB g, int vertex, int *output);

void printGraph_JRB(Graph_JRB g);
void dropGraph_JRB(Graph_JRB g);


#endif /* GRAPH_JRB_H */
