void add_all_vertices(Graph G, char *fn);
void add_all_edges(Graph G, char *fn);
void print_all_vertex(Graph G);
void print_all_adjacent(Graph G, int v);
void print_shortest_path(Graph G, int v, int v2);
int _increase_cmp(const void *a, const void *b);
void print_list_vertices(Graph G, int *output, int n);
int scan_int(const char *s);
int scan_char(const char *s);
void menu();

void menu(){
	puts("");
	puts("----------MENU----------");
	puts("1) Import data to graph, reprint matrix");
	puts("2) Show number of edge and matrix");
	puts("3) Get adjacent vertices");
	puts("4) Show shortest path");
	puts("5) Show nearest exit");
	puts("6) Show maximum flow");
	puts("7) Quit");
}

int scan_int(const char *s){//ok
	printf("%s", s);
	char temp[100];
	scanf("%[^\n]s", temp);
	getchar();
	return atoi(temp);
}

int scan_char(const char *s){//ok
	printf("%s", s);
	char temp[100];
	scanf("%[^\n]s", temp);
	getchar();
	return temp[0];
}

void _index_to_name(int i, int j, char *name){
	sprintf(name, "%d%d", i, j);
}

void add_all_vertices(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		printf("input file error!\n");
		return;
	}
	char *name;
	int i;
	while(get_line(is) >= 0){
		for(i=0; i<is->NF; i++){
			if(!atoi(is->fields[i])){
				name = (char*)malloc(sizeof(char)*10);
				_index_to_name(is->line-1, i, name);				
				add_vertex_auto_increment(G, name);
				log("add vertex: '%s'\n", name);
			}
		}
	}
	jettison_inputstruct(is);
}

void add_all_edges(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		printf("input file error!\n");
		return;
	}
	char name1[10], name2[10];
	int i, j;
	int v1, v2;
	int matrix[5][5];
	while(get_line(is) >= 0){
		for(i=0; i<is->NF; i++){
			matrix[is->line-1][i] = atoi(is->fields[i]);
		}
	}
	
	for(i=0; i<5; i++){
		for(j=0; j<4; j++){
			if(!matrix[i][j] && !matrix[i][j+1]){
				_index_to_name(i, j, name1);
				_index_to_name(i, j+1, name2);
				v1 = get_vertex_id(G, name1);
				v2 = get_vertex_id(G, name2);
				add_edge(G, v1, v2, 1, UNDIRECTED);
				// log("add edge '%s' '%s'\n", name1, name2);
			}
		}
	}
	for(j=0; j<5; j++){
		for(i=0; i<4; i++){
			if(!matrix[i][j] && !matrix[i+1][j]){
				_index_to_name(i, j, name1);
				_index_to_name(i+1, j, name2);
				v1 = get_vertex_id(G, name1);
				v2 = get_vertex_id(G, name2);
				add_edge(G, v1, v2, 1, UNDIRECTED);
				// log("add edge '%s' '%s'\n", name1, name2);
			}
		}
	}
	jettison_inputstruct(is);
}

void print_graph_as_matrix(Graph G){
	int i, j;
	char name[10];
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			_index_to_name(i, j, name);
			if(get_vertex_id(G, name) >= 0){
				printf("0 ");
			}else{
				printf("1 ");
			}
		}
		printf("\n");
	}
}

void print_list_vertices(Graph G, int *output, int n){//ok
	int i;
	for(i=0; i<n; i++)
		printf("    - %s\n", get_vertex_val(G, output[i]));
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
	printf("    - adjacent of '%s': ", get_vertex_val(G, v));
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
	int n1 = count_prequisites(G, v1);
	int n2 = count_prequisites(G, v2);
	if(n1 > n2)
		return 1;
	else if (n1 < n2)
		return -1;
	else
		return 0;
}
