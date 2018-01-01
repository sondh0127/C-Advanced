void print_all_vertex(Graph G);
void print_all_adjacent(Graph G, int v);
void print_shortest_path(Graph G, int v, int v2);
// int _increase_cmp(const void *a, const void *b);
void menu();

void menu(){
	puts("");
	puts("----------MENU----------");
	puts("1) Import data to graph");
	puts("2) Check consistentcy, a member cannot not be both mom and dad");
	puts("3) Check consistentcy, a member cannot has more than one mom or dad");
	puts("4) Check consistentcy, check circle in graph");
	puts("5) Print all sibling");
	puts("6) Print all grandchildren");
	puts("7) Print all descendances");
	puts("8) Quit");
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

// int _asc_cmp(const void *a, const void *b){
// 	int v1 = *(int*)a;
// 	int v2 = *(int*)b;
// 	int n1 = count_prerequisites(G, v1);
// 	int n2 = count_prerequisites(G, v2);
// 	if(n1 > n2)
// 		return 1;
// 	else if (n1 < n2)
// 		return -1;
// 	else
// 		return 0;
// }

int is_mom_or_dad_only(Graph G, int v){
	int n = count_vertices(G);
	int *output = (int*)malloc(sizeof(int)*n);
	int m = get_adjacent_vertices_out_edge(G, v, output);
	int i, v2;
	double w;
	int flag = UNDEFINED;
	for(i=0; i<m; i++){
		v2 = output[i];
		w = get_edge_weight(G, v, v2);
		if(flag == UNDEFINED){
			if(w != UNDEFINED)
				flag = w;
		}
		else{
			if(flag != w){
				free(output);
				return false;
			}
		}
	}
	free(output);	
	return true;
}

int no_more_than_one_mom_or_dad(Graph G, int v2){
	int n = count_vertices(G);
	int *output = (int*)malloc(sizeof(int)*n);
	int m = get_adjacent_vertices_in_edge(G, v2, output);
	int i, v;
	double w;
	int count_mom = 0, count_dad = 0;
	for(i=0; i<m; i++){
		v = output[i];
		w = get_edge_weight(G, v, v2);
		if(w==MOM)
			count_mom++;
		if(w==DAD)
			count_dad++;
	}
	free(output);
	if(count_mom<=1 && count_dad <=1)
		return true;
	else
		return false;
}

int in_array(int v, int *array, int n){
	int i;
	for(i=0; i<n; i++){
		if(array[i] == v)
			return true;
	}
	return false;
}

int get_sibling(Graph G, int v2, int *output){
	int mom, dad, i, v;
	double w;
	int n = count_vertices(G);
	int *parent = (int*)malloc(sizeof(int)*n);
	int m = get_adjacent_vertices_in_edge(G, v2, parent);
	for(i=0; i<m; i++){
		v = parent[i];
		w = get_edge_weight(G, v, v2);
		if(w==MOM)
			mom = v;
		if(w==DAD)
			dad = v;
	}

	for(i=0; i<n; i++)
		output[i] = 0;
	int total = 0;
	int *temp = (int*)malloc(sizeof(int)*n);

	m = get_adjacent_vertices_out_edge(G, mom, temp);
	for(i=0; i<m; i++){
		v = temp[i];
		if(!in_array(v , output, n) && v != v2)
			output[total++] = v;
	}
	m = get_adjacent_vertices_out_edge(G, dad, temp);
	for(i=0; i<m; i++){
		v = temp[i];
		if(!in_array(v , output, n) && v != v2)
			output[total++] = v;
	}
	free(temp);
	free(parent);
	return total;
}

int get_all_grand_children(Graph G, int v, int *output){
	int *children, *grandchildren, n, n_children, n_grandchildren, i, j, v2, v_child;
	n = count_vertices(G);
	children = (int*)malloc(sizeof(int) * n);
	grandchildren = (int*)malloc(sizeof(int) * n);
	n_children = get_adjacent_vertices_out_edge(G, v, children);

	for(i=0; i<n; i++)
		output[i] = 0;

	int total = 0;
	// printf("  -List of child:\n");
	// print_list_vertices(G, children, n_children);

	for(i=0; i<n_children; i++){
		v_child = children[i];
		n_grandchildren = get_adjacent_vertices_out_edge(G, v_child, grandchildren);
		for(j=0; j<n_grandchildren; j++){
			v2 = grandchildren[j];
			if(!in_array(v2 , output, n))
				output[total++] = v2;
		}

		// printf("  -List of child of '%s':\n", get_vertex_val(G, v_child));
		// print_list_vertices(G, grandchildren, n_grandchildren);
	}
	free(children);
	free(grandchildren);
	return total;
}


int _self;
void _print_a_descendant(Graph G, int v){
	if(v != _self)
		printf("    - '%s'\n", get_vertex_val(G, v));
}

void print_all_descendants(Graph G, int v){
	_self = v;
	dfs(G, v, -1, _print_a_descendant);
}