#ifndef API_H
#define API_H 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "../../lib/include/dllist.h"
#include "../../lib/include/fields.h"
#include "../../lib/include/jrb.h"
// API
int menu();

void add_all_vertices_and_edges(Graph G, char *fn);

int in_array(int v, int *array, int n);

void print_list_vertices(Graph G, int *output, int n);
void print_vertex(Graph G, int v);
int get_all_grand_parent(Graph G, int v, int *output); //chua test

int get_all_ancestor(Graph G, int v, int *output);
double get_shortest_time(Graph G, int v, int *output, int *n);

typedef struct {
	int A[100];
	int num;
	double weight;
} Array1;

void All_node_visited_a(Graph g,int v,Array1 *a,int stop);

Array1* All_node_visited(Graph g, int v);
//new
void print_by_level(Graph graph,int start,int stop,void(*func)(Graph, int));
double longest_path(Graph graph, int start, int stop, int *path, int *length); // not work
#endif