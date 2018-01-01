#include "api.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "../../lib/include/dllist.h"
#include "../../lib/include/fields.h"
#include "../../lib/include/jrb.h"
// API
int _cmp_int(const void *a, const void *b);
int menu() {
	int choose = 0;
	int MAX = 6;
	char menu[][100] = { "Import data to graph", 
	"Dinh lien ke", 
	"Khoang cach ngan nhat", 
	"Khoang cach ngan nhat thoat khoi me cung" ,
	"Thanh phan lien thong lon nhat",
	"Exit"};

	printf("\n\t\t================================\n");
	printf(  "\t\t============| MENU |============\n");
	printf(  "\t\t================================\n");
	for(int i = 0; i < MAX; i++)
		printf("\t%d) %s\n", i+1, menu[i]);
	printf("[+] Enter your chose: ");
	while(scanf("%d", &choose) != 1) {
		printf("	- Input must be integer!\n");
		while (getchar() != '\n' );
        //wasting the buffer till the next new line
		printf("[+] Enter your choose: ");
	}
	return choose;  
}

void _index_to_name(int i, int j, char *name) {
	sprintf(name, "%d%d", i ,j);
}
int _n_matrix(char *fn) {
	IS is = new_inputstruct(fn);
	if (!is) {
		printf("	- input error, no such file or directory!\n");
		return -1;
	}
	get_line(is);
	int n = is->NF;
	jettison_inputstruct(is);
	return n;
}
void add_all_vertices(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if (!is) {
		printf("	- input error, no such file or directory!\n");
		return;
	}
	char *name;
	int check;
	while(get_line(is) >= 0) {
		for (int i = 0; i < is->NF; i++){
			check = atoi(is->fields[i]);
			if (!check) {
				name = (char *) malloc(sizeof(char) *10);
				_index_to_name(is->line - 1, i, name);
				add_vertex_auto_increment(G, name);
				log(" add vertex: '%s'\n", name);
			}
		}
	}
	jettison_inputstruct(is);
}

void add_all_edges(Graph G, char *fn)
{
	IS is = new_inputstruct(fn);
	if (!is) {
		printf("	- input error, no such file or directory!\n");
		return;
	}
	char *name1, *name2;
	int v1, v2;
	// count number of row/col of maxtrix;
	get_line(is);
	int n = is->NF;
	fseek(is->f, 0, SEEK_SET);
	is->line--;
	//
	printf("n %d line %ld\n", n, ftell(is->f));
	int maxtrix[n][n];
	while(get_line(is) >= 0) {
		// printf("%d\n", is->line);
		for (int i = 0; i < is->NF; i++) {
			maxtrix[is->line-1][i] = atoi(is->fields[i]);
			// printf("%d ", maxtrix[is->line-1][i]);
		}
		// printf("\n");
	}
	name1 = (char *) malloc(sizeof(char) *10);
	name2 = (char *) malloc(sizeof(char) *10);
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", maxtrix[i][j]); 
		}
		printf("\n");
	}	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-1; j++) {
			if (!maxtrix[i][j] && !maxtrix[i][j+1]) {
				_index_to_name(i, j, name1);
				_index_to_name(i, j+1, name2);
				v1 = get_vertex_id(G, name1);
				v2 = get_vertex_id(G, name2);
				if (v1 != -1 && v2 != -1) {
					// log(" add edge '%d' '%d'\n", v1, v2);
					add_edge(G, v1, v2, 1, UNDIRECTED);
					// log(" add edge '%s' '%s'\n", name1, name2);
				}			
			}
		}
	}

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n-1; i++) {
			if (!maxtrix[i][j] && !maxtrix[i+1][j]) {
				_index_to_name(i, j, name1);
				_index_to_name(i+1, j, name2);
				v1 = get_vertex_id(G, name1);
				v2 = get_vertex_id(G, name2);
				add_edge(G, v1, v2, 1, UNDIRECTED);
				// log(" add edge '%s' '%s'\n", name1, name2);
			}
		}
	}
	jettison_inputstruct(is);
}


int get_all_out_door(Graph G, char *fn, int *output) {
	// int n_matrix = _n_matrix(fn);
	IS is = new_inputstruct(fn);
	if (!is) {
		printf("	- input error, no such file or directory!\n");
		return -1;
	}
	char *name;
	int check;
	int v;
	int total = 0;
	while(get_line(is) >= 0) {
		for (int i = 0; i < is->NF; i++) {
			if (i == 0 || i == is->NF-1 || is->line == 1 || is->line == is->NF) {
				check = atoi(is->fields[i]);
				if (!check) {
					name = (char *) malloc(sizeof(char) *10);
					_index_to_name(is->line - 1, i, name);
					v = get_vertex_id(G, name);
					output[total++] = v;
				}
			}	
		}
	}
	jettison_inputstruct(is);
	return total;
}

int in_array(int v, int *array, int n){
	int i;
	for(i=0; i<n; i++){
		if(array[i] == v)
			return true;
	}
	return false;
}

void print_list_vertices(Graph G, int *output, int n){//ok
	int i;
	for( i = 0; i < n; i++)
		printf("	- %s\n", get_vertex_name(G, output[i]));
}

int get_all_grand_parent(Graph G, int v, int *output)//chua test
{
	int *parent, *grandparent, n, n_parent, n_grandparent, v2, v_parent;
	n = count_vertices(G);
	parent = (int*)malloc(sizeof(int) * n);
	grandparent = (int*)malloc(sizeof(int) * n);
	n_parent = in_degree(G, v, parent);

	for(int i=0; i<n; i++)
		output[i] = 0;

	int total = 0;
	// printf("  -List of child:\n");
	// print_list_vertices(G, parent, n_parent);

	for(int i=0; i<n_parent; i++){
		v_parent = parent[i];
		n_grandparent = in_degree(G, v_parent, grandparent);
		for(int j=0; j<n_grandparent; j++){
			v2 = grandparent[j];
			if(!in_array(v2 , output, n))
				output[total++] = v2;
		}

		// printf("  -List of child of '%s':\n", get_vertex_name(G, v_parent));
		// print_list_vertices(G, grandparent, n_grandparent);
	}
	free(parent);
	free(grandparent);
	return total;
}

int get_all_ancestor(Graph G, int v, int *output)
{
	Dllist queue = new_dllist();
	int total = 0;
	JRB node;
	node = jrb_find_int(G.vertices, v);
	if (node != NULL) {
		JRB node2;
		jrb_traverse(node2, G.vertices){
			int v2 = jval_i(node2->key);
			if (is_adjacent(G, v2, v))
				dll_append(queue, new_jval_i(v2));
		}
	}

    // Traversing
	while(dll_empty(queue) != 1) {
        // Take the top element in the queue
		Dllist dll_tmp = dll_first(queue);
		int key = jval_i(dll_tmp->val);
		dll_delete_node(dll_tmp);
		if (!in_array(key, output, total)) {
			output[total++] = key;
		}

		node = jrb_find_int(G.vertices, key);
		if (node != NULL) {
			JRB node2;
			jrb_traverse(node2, G.vertices) {
				int v2 = jval_i(node2->key);
				if (is_adjacent(G, v2, key))
					dll_append(queue, new_jval_i(v2));
			}
		}

	}
	qsort(output, total, sizeof(int), _cmp_int);
	free_dllist(queue);
	return total;
}


Graph _G;
int _v;
int _cmp_weight_adjacent(const void *v1, const void *v2) {
	double a = get_edge_weight(_G, _v, *(int*)v1);
	double b = get_edge_weight(_G, _v, *(int*)v2);
	if (a < b) return 1;
	else if (a > b) return -1;
	else return 0;
}

int get_adjacent_sorted_by_weight(Graph G, int v, int* output)
{
	int total = out_degree(G, v, output);
	_G = G;
	_v = v;
	qsort(output, total, sizeof(int), _cmp_weight_adjacent);
	return total;
}

double get_shortest_time(Graph G, int v, int *output, int *n)
{
	Dllist queue = new_dllist();
	int total = 0;
	double max = -1000000;
	double weight, total_weight = 0;
	int id, count;
	int *parent;
	parent = (int*)malloc(sizeof(int) * count_vertices(G));
	count = in_degree(G, v, parent);
	for (int i = 0; i < count; i++) {
		weight = get_edge_weight(G, parent[i], v);
		printf("weight %.f\n", weight);
		if (weight > max) {
			max = weight;
			id = parent[i];
		}
	}
	printf("id %d\n", id);
	total_weight += max;
	dll_append(queue, new_jval_i(id));

    // Traversing
	while(dll_empty(queue) != 1) {
        // Take the top element in the queue
		Dllist dll_tmp = dll_first(queue);
		int key = jval_i(dll_tmp->val);
		dll_delete_node(dll_tmp);
		if (!in_array(key, output, total)) {
			output[total++] = key;
			printf("key %d\n", key);
		}

		count = in_degree(G, key, parent);
		if (count != 0) {
			max = -1000000;
			for (int i = 0; i < count; i++) {
				weight = get_edge_weight(G, parent[i], key);
				if (weight > max) {
					max = weight;
					id = parent[i];
					printf("check \n");
				}
			}
			dll_append(queue, new_jval_i(id));
			total_weight += max;
		}


	}
	*n = total;
	free_dllist(queue);
	return total_weight;
}



void All_node_visited_a(Graph g,int v,Array1 *a,int stop){
	int i,j,n;
	int output[100];
	int check;
	n= in_degree(g,v,output);
	if(n!=0){
		for(i=0;i<n;i++){
			check=0;
			for(j=0;j<a->num;j++){
				if(output[i]==a->A[j] || output[i]==stop){
					check=1;
					break; 
				} 
			}
			if(check==0){
				a->A[a->num]=output[i];
				a->num+=1;
				All_node_visited_a(g,output[i],a,stop);
			}
		}
	}
}

int _cmp_int(const void *a, const void *b) {
	return ( *(int*)a - *(int*)b );
}

Array1* All_node_visited(Graph g, int v){
	Array1* a;
	int n;
	int output[100];
	a=(Array1*)malloc(sizeof(Array1));
	a->num=0;
	n = in_degree(g,v,output); 
	if (n != 0) {
		for (int i = 0; i < n; i++) {
			a->A[i] = output[i];
			a->num+= 1;
		}
		for (int i = 0; i < n; i++) {
			All_node_visited_a(g, output[i], a, v);
		}
		qsort(a->A, a->num, sizeof(int), _cmp_int);
	}
	return a;
}

int dfs2(Graph graph, int start, int stop, int *path)
{
	int total = 0;
	JRB check1 = jrb_find_int(graph.vertices,start);
	JRB check2 = jrb_find_int(graph.vertices,stop);
	if(check1 == NULL ) {
		printf("Graph does not have vertex %d\n", start);
		return -1;
	}
	if(stop != -1 && check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
		return -1;
	}
	
	// Create a Graph name 'parent' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // parent (1) or not (0)
	JRB parent = make_jrb();
	JRB ptr;
	int V = 0;
	jrb_traverse(ptr, graph.vertices) {
		V++;
		jrb_insert_int(parent, jval_i(ptr->key), new_jval_i(0));
	}
	int output[V];

    // Create a stack and push the first element
	Dllist stack = new_dllist();
	dll_append(stack, new_jval_i(start));

    // Traversing
	while(dll_empty(stack) != 1) {
        // Take the top element in the stack
		Dllist dll_tmp = dll_last(stack);
		int key = jval_i(dll_tmp->val);

		JRB tmp = jrb_find_int(parent, key);
		if(jval_i(tmp->val) == 0) {
        	// Pass the vertex to external function
			path[total++] = key;
	        // Mark this element as 'parent'
			jrb_delete_node(tmp);
			jrb_insert_int(parent, key, new_jval_i(1));
		} else {
			// Pop this element
			dll_delete_node(dll_tmp);
		}

		// If this is the required vertex, return
		if (key == stop) {
			free_dllist(stack);
			jrb_free_tree(parent);
			return total;
		}

		int count = out_degree(graph, key, output);
		for (int i = count -1 ; i >= 0; i--)
		{
	            // If the vertice has not been parent, push it
			tmp = jrb_find_int(parent, output[i]);
			if (jval_i(tmp->val) == 0) {
				key = jval_i(tmp->key);
				dll_append(stack, new_jval_i(key));
			}
		}
	}
	free_dllist(stack);
	jrb_free_tree(parent);
	return total;
}