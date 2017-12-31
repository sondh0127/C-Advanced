#include "api.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include <assert.h>
#include "../../lib/include/dllist.h"
#include "../../lib/include/fields.h"
#include "../../lib/include/jrb.h"
// API
int menu() {
	int choose = 0;
	int MAX = 6;
	char menu[][100] = { "In danh sach san pham", 
	"In danh sach giao dich", 
	"Hien thi muc do lien quan giua 2 san pham", 
	"In danh sach cac san pham lien quan" ,
	"Hien thi lien he giua hai san pham",
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

void print_all_vertices(Graph graph)
{
	JRB ptr;
	jrb_traverse(ptr, graph.vertices) {
		printf("\n	Ma san pham:'%d'\n	Ten san pham: '%s'\n", jval_i(ptr->key), get_vertex_name(graph, jval_i(ptr->key)));
	}
}

void add_all_vertices(Graph G, char *fn) {
	IS is = new_inputstruct(fn);
	if (!is) {
		printf("	- input error, no such file or directory!\n");
		return;
	}
	char *name;
	int v;
	while(get_line(is) >= 0) {
		v = atoi(is->fields[0]);
		name = (char *)malloc(sizeof(char)*100);
		strcpy(name, is->fields[1]);

		add_vertex(G, v, name);
		v = get_vertex_id(G, name);
		// printf("v: %d\n", v);
	}
	jettison_inputstruct(is);
}

void change_weight(Graph G, int v, int v2, double newWeight, int mode)
{
	assert(G.edges);

	JRB node = jrb_find_int(G.edges, v);
	JRB node2;
	JRB tree;
	if (node == NULL) {
		return;
	} else {
		tree = (JRB) jval_v(node->val);
		node2 = jrb_find_int(tree, v2);
		jrb_delete_node(node2);
		add_edge(G, v, v2, newWeight, mode);
	}
}

void add_all_edges(Graph G, char *fn) {
	IS is = new_inputstruct(fn);
	if (!is) {
		printf("	- input error, no such file or directory!\n");
		return;
	}
	int v, v2;
	while(get_line(is) >= 0) {
		printf("	");
		for (int i = 0; i < is->NF; i++) {
			v = atoi(is->fields[i]);
			printf("%s ", get_vertex_name(G, v));
			for (int j = i; j < is->NF; j++) {
				v2 = atoi(is->fields[j]);
				if (v != v2) {
					// printf(" %d-%d\n", v, v2);
					if (is_adjacent(G, v, v2)) {
						change_weight(G, v, v2, get_edge_weight(G, v, v2) + 1, UNDIRECTED);
					}
					else {
						add_edge(G, v, v2, 1, UNDIRECTED);
					}
				}
				
			}
		}
		printf("\n");
	}
	jettison_inputstruct(is);
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

void print_vertices_name(Graph G, int v)
{
	printf("%s ", get_vertex_name(G, v));
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

int get_all_ancestor(Graph G, int v, int *output, int n_parent)
{

	return 0;
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
	return ( *(int*)b - *(int*)a );
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