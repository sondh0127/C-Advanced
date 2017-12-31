#ifndef GRAPH_H
#define GRAPH_H
#include "../../lib/include/jrb.h"

#define true 1
#define false 0
#define UNDIRECTED 0
#define DIRECTED 1
#define INFINITY 2000000000
#define UNDEFINED -1
// #define log(...) printf("")	
#ifndef log
	#define log(...) printf("[+]" __VA_ARGS__)
#endif

typedef struct Graph{
	JRB vertices; 
	JRB edges;
} Graph;

Graph create_graph();

void add_vertex(Graph G, int id, char *name);

void add_vertex_auto_increment(Graph G, char *name);
char *get_vertex_name(Graph G, int id);
int get_vertex_id(Graph G, char *name);
int get_vertices_id(Graph G, int *output);

int count_vertices(Graph G);
int get_graph_max_id(Graph G);
int get_graph_min_id(Graph G);

void _add_edge(Graph G, int v, int v2, double weight);
void add_edge(Graph G, int v, int v2, double weight, short mode);

double get_edge_weight(Graph G, int v, int v2);
int count_edges(Graph G, short mode);

int is_adjacent(Graph G, int v, int v2);
int out_degree(Graph G, int v, int *output);
int in_degree(Graph G, int v2, int *output);

// modified
double shortest_path(Graph graph, int start, int stop, int *path, int *length);

void drop_graph(Graph *G);

int count_adjacent(Graph G, int v);
int _cmp_count_adjacent_asc(const void *v1, const void *v2);
void get_vertices_sorted_by_adjacent(Graph G, int *output);


//get error if graph does not interconnected
void bfs(Graph graph,int start,int stop,void(*func)(Graph, int));
void dfs(Graph graph, int start, int stop, void (*func)(Graph, int));

int is_cycle_vertex(Graph graph, int start);
int is_cycle(Graph graph); // not sure

void print_graph(Graph graph);

void topological_sort(Graph graph, void (*visit)(int));
void topological_sort_t(Graph g, int *output, int *n);

void topologicalSort_no_counti(Graph g, int * output, int * n);

#endif /* GRAPH_JRB_H */
