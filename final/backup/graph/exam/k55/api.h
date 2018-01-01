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
	puts("1) Import data to graph");
	puts("2) Show info of job must be done");
	puts("3) Show list of job sorted by topo");
	puts("4) Show minimum time to accomplist a job");
	puts("5) Validate data");
	puts("6) Quit");
}

void _index_to_name(int i, char *name){
	sprintf(name, "%d", i);
}

int scan_int(const char *s){
	printf("%s", s);
	char temp[100];
	scanf("%[^\n]s", temp);
	getchar();
	return atoi(temp);
}

int scan_char(const char *s){
	printf("%s", s);
	char temp[100];
	scanf("%[^\n]s", temp);
	getchar();
	return temp[0];
}

void add_all_vertices(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		printf("error!\n");
		return;
	}
	char *name;
	while(get_line(is) >= 0){
		name = (char*)malloc(sizeof(char)*10);
		strcpy(name, is->fields[0]);
		add_vertex_auto_increment(G, name);
		log("add vertex: '%s'\n", name);
	}
	jettison_inputstruct(is);
}

void add_all_edges(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		printf("error!\n");
		return;
	}
	char name1[10], name2[10];
	int v1, v2, i;
	double w;
	char *token;
	char temp[100];
	while(get_line(is) >= 0){
		strcpy(name2, is->fields[0]);
		for(i=2; i<is->NF; i++){
			strcpy(temp, is->fields[i]);
			token = strtok(temp, "-");
			if(token){
				strcpy(name1, token);
				token = strtok(NULL, "-");
				w = atof(token);
				v1 = get_vertex_id(G, name1);
				v2 = get_vertex_id(G, name2);
				if(v1 < 0 || v2 < 0)
					continue;
				add_edge(G, v1, v2, w, DIRECTED);
				log("add edge %s -> %s weight=%f\n", name1, name2, w);	
			}
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
	int n1 = count_prequisites(G, v1);
	int n2 = count_prequisites(G, v2);
	if(n1 > n2)
		return 1;
	else if (n1 < n2)
		return -1;
	else
		return 0;
}
