void add_all_vertices(Graph G, char *fn);
void add_all_edges(Graph G, char *fn);
void print_all_vertex(Graph G);
void print_all_adjacent(Graph G, int v);
void print_shortest_path(Graph G, int v, int v2);
int _increase_cmp(const void *a, const void *b);
int scan_int(const char *s);
void menu();

void menu(){
	puts("");
	puts("----------MENU----------");
	puts("1) People statistic");
	puts("2) Graph statistic");
	puts("3) Friendlist");
	puts("4) Check mutual friends status");
	puts("5) Quit");
}

void _index_to_name(int i, char *name){
	sprintf(name, "%d", i);
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

void add_all_vertices(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		puts("input file error!");
		return;
	}
	char *name; int i;
	while(get_line(is) >= 0){

		for(i=0; i<is->NF; i+=2){
			name = (char*)malloc(sizeof(char)*10);
			strcpy(name, is->fields[i]);
			add_vertex_auto_increment(G, name);
			log("add vertex: '%s'\n", name);
		}
	}
	jettison_inputstruct(is);
}

void add_all_edges(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		puts("input file error!");
		return;
	}
	char name1[100], name2[100];
	int v1, v2, i;
	while(get_line(is) >= 0){
		if(is->NF > 2){
			strcpy(name1, is->fields[0]);
			strcpy(name2, is->fields[2]);
			v1 = get_vertex_id(G, name1);
			v2 = get_vertex_id(G, name2);
			if (v1 < 0 || v2 < 0)
				continue;
			add_edge(G, v1, v2, 1, UNDIRECTED);
			log("add edge '%s' '%s'\n", name1, name2);			
		}
	}
	jettison_inputstruct(is);
}

void print_all_vertices(Graph G){//ok
	JRB node, tree;
	tree = G.vertices;
	jrb_traverse(node, tree){
		printf("        id:'%d' value: '%s'\n",jval_i(node->key), get_vertex_val(G, jval_i(node->key)));
	}
}

void print_list_vertices(Graph G, int *output, int n){
	int i;
	for(i=0; i<n; i++)
		printf("    - %s\n", get_vertex_val(G, output[i]));
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
