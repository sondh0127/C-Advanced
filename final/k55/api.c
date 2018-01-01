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

void print_vertex(Graph G, int v){//ok
	printf("	- %s", get_vertex_name(G, v));
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

void print_by_level(Graph graph,int start,int stop,void(*func)(Graph, int))
{
	JRB check1 = jrb_find_int(graph.vertices,start);
	JRB check2 = jrb_find_int(graph.vertices,stop);
	if (check1 == NULL ) {
		printf("Graph does not have vertex %d\n", start);
		return;
	}
	if (stop != -1 && check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
		return;
	}
	JRB visited = make_jrb();
	JRB ptr;
	int V = 0;
	jrb_traverse(ptr,graph.vertices) {
		V++;
		jrb_insert_int(visited, jval_i(ptr->key), new_jval_i(0));
	}
	int output[V];
	
	int total = 1;
	Dllist queue = new_dllist();
	Dllist children = new_dllist();
	int n = out_degree(graph, start, output);
	for (int i = 0; i < n; i++)	{
		dll_append(queue,new_jval_i(output[i])); 
	}
	// Traversing
	printf("\nLevel %d: ", total ++);
	while(dll_empty(queue) != 1) {
		// Take first element in the queue
		Dllist node = dll_first(queue);
		int key = jval_i(node->val);
		// Dequeue this element
		dll_delete_node(node);
		
		JRB tmp = jrb_find_int(visited, key);
		if(jval_i(tmp->val) == 0) {
			// Pass the vertex to external function
			func(graph, key);
			// Mark this element as 'visited'
			jrb_delete_node(tmp);
			jrb_insert_int(visited, key, new_jval_i(1));		
		}

		// If this is the required vertex, return
		if (key == stop) {
			free_dllist(queue);
			jrb_free_tree(visited);
			return;
		}
		
		int count = out_degree(graph, key, output);
		for (int i = 0; i < count; i++)
		{
			JRB ptr = jrb_find_int(visited, output[i]);
			if(jval_i(ptr->val) == 0)
				dll_append(children,new_jval_i(output[i])); 
		}
		if (dll_empty(queue) && !dll_empty(children)) {
			printf("\nLevel %d: ", total ++);
			while (dll_empty(children) != 1) {
				Dllist node2 = dll_first(children);
				int key2 = jval_i(node2->val);
				dll_delete_node(node2);
				dll_append(queue, new_jval_i(key2));
			}
		}
	}
	free_dllist(queue);
	jrb_free_tree(visited);
}

double longest_path(Graph graph, int start, int stop, int *path, int *length)
{
	// main variable
	JRB parent = make_jrb();
	JRB distance = make_jrb();
	JRB visited = make_jrb();
	Dllist queue = new_dllist();
	JRB node;
	// Return if the first or last node is not valid
	JRB check1 = jrb_find_int(graph.vertices, start);
	JRB check2 = jrb_find_int(graph.vertices, stop);

	if (check1 == NULL) {
		printf("Graph does not have vertex %d\n", start);
		return -INFINITY;
	}
	if (check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
		return -INFINITY;
	}

	int V = 0;
	jrb_traverse(node, graph.vertices) {
		int key = jval_i(node->key);
		double dist = -INFINITY;
		if (key == start) {
			dist = 0;
		}
		jrb_insert_int(distance, key, new_jval_d(dist));
		jrb_insert_int(parent, key, new_jval_i(-1));
		jrb_insert_int(visited, key, new_jval_i(0));
		V++;
	}

	// Create a priority queue, it which the order is determined by the distance to that node from the sing node
    // At first, the sing node will be the first element, since its distance would be 0, and the rest is -INFINITY
	
	jrb_traverse(node, graph.vertices) {
		int key = jval_i(node->key);
		if (key == start) {
			dll_prepend(queue, new_jval_i(key));
		} else {
			dll_append(queue, new_jval_i(key));
		}
	}

	while(dll_empty(queue) != 1) {
		Dllist temp = dll_first(queue);
		int key = jval_i(temp->val);

		// If the first element in the queue is the node we are looking for,
        // that mean the path we took to it is shortest
		int adjacents[100];
		if (key == stop) {
			int total = 0;
			// Look up all the node in JRB parent
			while (key != -1) {
				// Use adjacents[] as a middle array,
                // since the way we traverse will return the node in reverse order
				adjacents[total++] = key;
				key = jval_i(jrb_find_int(parent, key)->val);
			}
			// Return the correct path order
			for (int i = 0; i < total; i++) {
				path[i] = adjacents[total - 1 - i];
			}
			// Return the total number of node in the route
			*length = total;

			// Return the total weight; 
			return jval_d(jrb_find_int(distance, stop)->val);
		}

		// Dequeue the first element
		dll_delete_node(temp);

		
		// find current distance from distance list;
		double toKey = jval_d(jrb_find_int(distance, key)->val);

		int count = out_degree(graph, key, adjacents);
		for (int i = 0; i < count; i++) {
			JRB node_temp = jrb_find_int(visited, adjacents[i]);
			if (jval_i(node_temp->val) == 0) {
				jrb_delete_node(node_temp);
				jrb_insert_int(visited, adjacents[i], new_jval_i(1));

				int adjKey = adjacents[i];
				double weight = get_edge_weight(graph, key, adjKey);
				double toAdj = jval_d(jrb_find_int(distance, adjKey)->val);
			// If the path to adjacent node can be shorten
			// by going through the current node
			// we set its parent to the current node
				if (toKey + weight > toAdj) {
				// set new distance
					toAdj = toKey + weight;
					node = jrb_find_int(distance, adjKey);
					jrb_delete_node(node);
					jrb_insert_int(distance, adjKey, new_jval_d(toAdj));

				// set new parent
					node = jrb_find_int(parent, adjKey);
					jrb_delete_node(node);
					jrb_insert_int(parent, adjKey, new_jval_i(key));

				// Dequeue the adjacent node and re-add it to the queue to maintain the priority
					dll_traverse(temp, queue) {
						if (jval_i(temp->val) == adjKey) {
							dll_delete_node(temp);
							break;
						}
					}

					dll_traverse(temp, queue) {
						int qKey = jval_i(temp->val);
						double dist = jval_d(jrb_find_int(distance, qKey)->val);
						if (dist < toAdj) {
							dll_insert_b(temp, new_jval_i(adjKey));
							break;
						}
					}
				}
			}
		}
	}
	free_dllist(queue);
	jrb_free_tree(parent);
	jrb_free_tree(distance);
	return -INFINITY;
}