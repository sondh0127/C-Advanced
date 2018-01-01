#include "../libfdr/dllist.h"
#include "../libfdr/fields.h"
#include "../libfdr/jval.h"
#include "../libfdr/jrb.h"

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
}Graph;

Graph create_graph ();

void add_vertex(Graph G, int id, char *name);
void add_vertex_auto_increment(Graph G, char *name);
char *get_vertex_val(Graph G, int id);
int get_vertex_id(Graph G, char *name);
int count_vertices(Graph G);
int get_vertices_id(Graph G, int *output);

void add_edge(Graph G, int v, int v2, double weight, short mode);
int has_edge(Graph G, int v, int v2);
double get_edge_weight(Graph G, int v, int v2);
int count_edges(Graph G, short mode);

int is_adjacent(Graph G, int v, int v2);
int get_adjacent_vertices(Graph G, int v, int *output);
int count_adjacent(Graph G, int v);
int get_adjacent_vertices_in_edge(Graph G, int v2, int *output);
int get_adjacent_vertices_out_edge(Graph G, int v, int *output);
void get_vertices_sorted_by_adjacent(Graph G, int *output);

int out_degree(Graph G, int v, int *output);
int in_degree(Graph G, int v, int *output);

void drop_graph(Graph *G);

void bfs(Graph G, int start, int stop, void (*visited_func)(Graph, int));
void dfs(Graph G,  int start, int stop, void (*visited_func)(Graph, int));

int get_graph_max_id(Graph G);
int get_graph_min_id(Graph G);

int is_cyclic(Graph G);

void topological_sort(Graph G, void (*visited_func)(Graph, int));
void get_topological_queue(Graph G, int *output, int *length);
int count_prequisites(Graph G, int v);

int has_path(Graph G, int s, int t);
int get_related_vertices(Graph G, int v, int *output);
double shortest_path(Graph G, int s, int t, int* path, double* length);
double topological_get_minimum_cost(Graph G, int v2);

int shortest_path_length(Graph G, int s, int t);
int get_path_length(Graph G, int *path);
int get_related_vertices_sorted_by_path_length(Graph G, int v, int *output);
int get_related_vertices_by_length(Graph G, int v, int length, int *output);

double get_path_weight(Graph G, int *path, int total);
double get_path_weight_v2(Graph G, int *path);
double shortest_path_weight(Graph G, int s, int t);
int get_related_vertices_sorted_by_path_weight(Graph G, int v, int *output);

int get_connected_vertices(Graph G, int v, int *output);
int _count_connected_vertices(Graph G, int v);
int get_maximum_connected_part(Graph G, int *output);
int get_minimum_connected_part(Graph G, int *output);

void print_all_path(Graph G, int s, int t);