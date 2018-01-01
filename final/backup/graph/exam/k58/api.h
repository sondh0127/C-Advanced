void add_all_vertex(Graph G, int matrix[][5]);
void add_all_edge(Graph G, int matrix[][5]);
void print_all_vertex(Graph G);
void print_all_adjacent(Graph G, int v);
void print_shortest_path(Graph G, int v, int v2);
int _increase_cmp(const void *a, const void *b);
void get_topological_queue(Graph G, int *output, int *length);
int count_prerequisites(Graph G, int v);
void menu();
void menu6(Graph G, int v);

void menu(){
	puts("");
	puts("----------MENU----------");
	puts("1) Import data to graph");
	puts("2) Check cyclic property");
	puts("3) Check subject prerequisite");
	puts("4) Print all path");
	puts("5) Print subjects sort by number of prerequisites ascending");
	puts("6) Print subjects order sort by topo");
	puts("7) Quit");
}

void _index_to_name(int i, char *name){
	sprintf(name, "%d", i);
}

void add_all_vertex(Graph G, int matrix[][5]){
	log("[+] adding all vertex\n");
	log("[+] success!\n");
}

void add_all_edge(Graph G, int matrix[][5]){
	log("adding all edge\n");
	log("[+] success!\n");
}

void print_all_vertices(Graph G){//ok
	JRB node, tree;
	tree = G.vertices;
	jrb_traverse(node, tree){
		printf("        id:'%d' value: '%s'\n",jval_i(node->key), get_vertex_val(G, jval_i(node->key)));
	}
}

void print_all_adjacent(Graph G, int v){//ok
	int *output, i, n;
	n = count_adjacent(G, v);
	output = (int*)malloc(sizeof(int) * n);
	get_adjacent_vertices(G, v, output);
	printf("adjacent of '%s': ", get_vertex_val(G, v));
	for(i=0; i<n; i++)
		printf("%s ", get_vertex_val(G, output[i]));
	putchar('\n');
	free(output);
}

void print_shortest_path(Graph G, int v, int v2){//ok
	int *path = (int*)malloc(100*sizeof(int));
	double *length = (double*)malloc(100*sizeof(double));
	int ret = shortest_path(G, v, v2, path, length), i;
	for(i=0; path[i]!=-1; i++);
	i--;
	for(; i>0; i--)
		printf("%s->", get_vertex_val(G, path[i]));
	printf("%s\n", get_vertex_val(G, path[0]));
	free(path);
	free(length);
}

int _asc_cmp(const void *a, const void *b){
	int v1 = *(int*)a;
	int v2 = *(int*)b;
	int n1 = count_prerequisites(G, v1);
	int n2 = count_prerequisites(G, v2);
	if(n1 > n2)
		return 1;
	else if (n1 < n2)
		return -1;
	else
		return 0;
}

int count_prerequisites(Graph G, int v){
	int *output = (int*)malloc(sizeof(int) * count_vertices(G));
	int length;
	get_topological_queue(G, output, &length);
	int count = 0, i;
	for(i=0; i<length; i++){
		if(output[i]==v)
			break;
		count++;
	}
	free(output);
	return count;
}

void menu6(Graph G, int v){
	printf("    %s\n", get_vertex_val(G, v));
}