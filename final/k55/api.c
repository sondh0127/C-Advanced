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
	"Show info of job must be done", 
	"Show list of job sorted by topo", 
	"Show minimum time to accomplist a job" ,
	"Validate data (topo)",
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

void add_all_vertices_and_edges(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if (!is) {
		printf("	- input error, no such file or directory!\n");
		return;
	}
	char *name, *name2, *w;
	int v, v2;
	double weight;
	while(get_line(is) >= 0) {
		name = (char *)malloc(sizeof(char)*10);
		strcpy(name, is->fields[0]);
				// insert to G

		add_vertex_auto_increment(G, name);
		v = get_vertex_id(G, name);
		printf("%d :", v);
		for (int i = 2; i < is->NF; i++) {
			name2 = (char *)malloc(sizeof(char)*10);
			w = (char *)malloc(sizeof(char)*5);
			sscanf(is->fields[i], "%2s-%s", name2, w);
			weight = atof(w);
			v2 = get_vertex_id(G, name2);
			add_edge(G, v2, v, weight, DIRECTED);
			printf(" %d-%.f", v2, weight);
		}
		printf("\n");
	}
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