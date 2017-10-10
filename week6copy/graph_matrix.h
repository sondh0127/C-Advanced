typedef struct {
	int * matrix;
	int size_max;
} graph;

extern graph create_graph(int size_max);
extern void add_edge(graph g, int v, int v2);
extern int isAdjacent(graph g, int v, int v2);
extern int getAdjacentVertices(graph g, int vertex, int *output);
extern void dropGraph(graph g);

void printGraph(graph g);
