#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../../lib/include/dllist.h"
#include "../../lib/include/jrb.h"

Graph create_graph()
{
	Graph newGraph;
	newGraph.edges = make_jrb();
	newGraph.vertices = make_jrb();

	return newGraph;
}

Graph _G;

void add_vertex(Graph G, int id, char *name)
{
	assert(G.vertices);
	JRB node = jrb_find_int(G.vertices, id);

	if (node == NULL) {
		jrb_insert_int(G.vertices, id, new_jval_s(name));
	} else {
		printf("Vertex already existed!\n");
	}
}

void add_vertex_auto_increment(Graph G, char *name)
{
	assert(G.vertices);
	if (get_vertex_id(G, name) != UNDEFINED)
		return;
	int v = get_graph_max_id(G) + 1;
	add_vertex(G, v, name);
}

char *get_vertex_name(Graph G, int id)
{
	JRB node = jrb_find_int(G.vertices, id);
	if (node != NULL)
		return jval_s(node->val);
	return NULL;
}

int get_vertex_id(Graph G, char *name)
{
	JRB node, tree;
	tree = G.vertices;
	jrb_traverse(node, tree) {
		if (!strcmp(name, jval_s(node->val)))
			return jval_i(node->key);
	}
	return UNDEFINED;
}

int get_vertices_id(Graph G, int *output)
{
	JRB node;
	int total = 0;
	jrb_traverse(node, G.vertices) {
		output[total++] = jval_i(node->key);
	}
	return total;
}

int count_vertices(Graph G)
{
	JRB node, tree;
	tree = G.vertices;
	int count = 0;
	jrb_traverse(node, tree) {
		count++;
	}
	return count;
}

int get_graph_max_id(Graph G)
{
	int max_id = 0;
	int key;
	JRB tmp;
	jrb_traverse(tmp, G.vertices) {
		key = jval_i(tmp->key);
		if (key > max_id)
			max_id = key;
	}
	return max_id;
}

int get_graph_min_id(Graph G)
{
	int min_id = INFINITY;
	int key;
	JRB tmp;
	jrb_traverse(tmp, G.vertices) {
		key = jval_i(tmp->key);
		if (key < min_id)
			min_id = key;
	}
	return min_id;
}

int is_adjacent(Graph G, int v, int v2)
{
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if(node == NULL)
		return false;
	tree = (JRB) jval_v(node->val);
	JRB f = jrb_find_int(tree, v2);
	if(f != NULL)
		return true;
	return false;
}

void _add_edge(Graph G, int v, int v2, double weight)
{
	assert(G.edges);
	if (is_adjacent(G, v, v2)){
		return;
	}
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if (node == NULL) {
		tree = make_jrb();
		jrb_insert_int(G.edges, v, new_jval_v(tree));
	} else {
		tree = (JRB) jval_v(node->val);
	}
	jrb_insert_int(tree, v2, new_jval_d(weight));	
}

void add_edge(Graph G, int v, int v2, double weight, short mode){
	_add_edge(G, v, v2, weight);
	if(mode == UNDIRECTED){
		_add_edge(G, v2, v, weight);
	}
}

double get_edge_weight(Graph G, int v, int v2)
{
	if (v == v2)
		return 0;
	JRB node = jrb_find_int(G.edges, v);
	if (node != NULL) {
		JRB tree = (JRB) jval_v(node->val);
		JRB node2 = jrb_find_int(tree, v2);
		if (node2 != NULL) return jval_d(node2->val);
	}
	return INFINITY;
}

int count_edges(Graph G, short mode)
{
	JRB node_tree, tree, node_sub_tree, sub_tree;
	tree = G.edges;
	int count = 0;
	jrb_traverse(node_tree, tree){
		sub_tree = (JRB) jval_v(node_tree->val);
		if(sub_tree)
			jrb_traverse(node_sub_tree, sub_tree)
		count++;
	}
	return mode == DIRECTED ? count : count/2;
}


int out_degree(Graph G, int v, int *output)
{
	int total = 0;
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if(node != NULL) {
		tree = (JRB) jval_v(node->val);
		jrb_traverse(node, tree){
			output[total++] = jval_i(node->key);
		}
	}
	return total;
}

int in_degree(Graph G, int v, int *output)
{
	int total = 0;
	JRB node = jrb_find_int(G.vertices, v);
	if (node != NULL) {
		JRB node2;
		jrb_traverse(node2, G.vertices){
			int v2 = jval_i(node2->key);
			if (is_adjacent(G, v2, v))
				output[total++] = v2;
		}
	}
	return total;
}

double shortest_path(Graph graph, int start, int stop, int *path, int *length)
{
	// main variable
	JRB parent = make_jrb();
	JRB distance = make_jrb();
	Dllist queue = new_dllist();
	JRB node;
	// Return if the first or last node is not valid
	JRB check1 = jrb_find_int(graph.vertices, start);
	JRB check2 = jrb_find_int(graph.vertices, stop);

	if (check1 == NULL) {
		printf("Graph does not have vertex %d\n", start);
		return INFINITY;
	}
	if (check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
		return INFINITY;
	}

	// We maintain two informations about each node:
    // the parent node (the node it come from) and the distance from the sing node
    // by traversing through the parent node
    int V = 0;
	jrb_traverse(node, graph.vertices) {
		int key = jval_i(node->key);
		double dist = INFINITY;
		if (key == start) {
			dist = 0;
		}
		// At first, all node does not have a parent, and its distance will be set to INFINITY,
        // except for the sing node
		jrb_insert_int(distance, key, new_jval_d(dist));
		jrb_insert_int(parent, key, new_jval_i(-1));
		V++;
	}

	// Create a priority queue, it which the order is determined by the distance to that node from the sing node
    // At first, the sing node will be the first element, since its distance would be 0, and the rest is INFINITY
	
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
                adjacents[total] = key;
                total++;
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
			int adjKey = adjacents[i];
			double weight = get_edge_weight(graph, key, adjKey);
			double toAdj = jval_d(jrb_find_int(distance, adjKey)->val);
			// If the path to adjacent node can be shorten
			// by going through the current node
			// we set its parent to the current node
			if (toKey + weight < toAdj) {
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
					if (dist > toAdj) {
						dll_insert_a(temp, new_jval_i(adjKey));
						break;
					}
				}
			}
		}
	}
	free_dllist(queue);
	jrb_free_tree(parent);
	jrb_free_tree(distance);
	return INFINITY;
}


void bfs(Graph graph,int start,int stop,void(*func)(Graph, int))
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
	// Create a Graph name 'parent' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // parent (1) or not (0)
	JRB parent = make_jrb();
	JRB ptr;
	int V = 0;
	jrb_traverse(ptr,graph.vertices) {
		V++;
		jrb_insert_int(parent, jval_i(ptr->key), new_jval_i(0));
	}
	int output[V];
	
	// Create a queue and enqueue the first element
	Dllist queue = new_dllist();
	dll_append(queue,new_jval_i(start));
	// Traversing
	while(dll_empty(queue) != 1) {
		// Take first element in the queue
		Dllist node = dll_first(queue);
		int key = jval_i(node->val);
		// Dequeue this element
		dll_delete_node(node);
		
		JRB tmp = jrb_find_int(parent, key);
		if(jval_i(tmp->val) == 0) {
			// Pass the vertex to external function
			func(graph, key);
			// Mark this element as 'parent'
			jrb_delete_node(tmp);
			jrb_insert_int(parent, key, new_jval_i(1));		
		}

		// If this is the required vertex, return
		if (key == stop) {
			free_dllist(queue);
			jrb_free_tree(parent);
			return;
		}
		
		int count = out_degree(graph, key, output);
		for (int i = 0; i < count; i++)
		{
			JRB ptr = jrb_find_int(parent, output[i]);
			if(jval_i(ptr->val) == 0)
				dll_append(queue,new_jval_i(output[i])); 
		}

	}
	free_dllist(queue);
	jrb_free_tree(parent);
}

// dfs ..........................................................

void dfs(Graph graph, int start, int stop, void (*func)(Graph, int))
{

	JRB check1 = jrb_find_int(graph.vertices,start);
	JRB check2 = jrb_find_int(graph.vertices,stop);
	if(check1 == NULL ) {
		printf("Graph does not have vertex %d\n", start);
		return;
	}
	if(stop != -1 && check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
		return;
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
			func(graph, key);
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
			return;
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
}


int is_cycle_vertex(Graph graph, int start)
{
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
    // printf("\n");
	while(dll_empty(stack) != 1) {
        // Take the top element in the stack
		Dllist dll_tmp = dll_last(stack);
		int key = jval_i(dll_tmp->val);

		JRB tmp = jrb_find_int(parent, key);
		if(jval_i(tmp->val) == 0) {
        	// Pass the vertex to external function
			//printf("%4d ", key);
	        // Mark this element as 'parent'
			jrb_delete_node(tmp);
			jrb_insert_int(parent, key, new_jval_i(1));
		} else {
			// Pop this element
			dll_delete_node(dll_tmp);
		}
		int count = out_degree(graph, key, output);
		for (int i = count -1 ; i >= 0; i--) {
			if (start == output[i])
			{
				jrb_free_tree(parent);
				free_dllist(stack);
				return 1;
			}
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
	return 0;
}

int is_cycle(Graph graph)
{	
	JRB ptr;
	jrb_traverse(ptr,graph.edges) {
		if(is_cycle_vertex(graph,jval_i(ptr->key)) == 1)
			return 1;
	}
	return 0;
}

void print_all_vertices(Graph graph)
{
	JRB ptr;
	jrb_traverse(ptr, graph.vertices) {
		printf("	id:'%d' name: '%s'\n", jval_i(ptr->key), get_vertex_name(graph, jval_i(ptr->key)));
	}
}

void print_graph(Graph graph)
{
	int v,v2;
	JRB ptr;	
	jrb_traverse(ptr, graph.edges) {
		v = jval_i(ptr->key);
		printf("	v: '%s': ", get_vertex_name(graph, v));
		JRB tree = (JRB) jval_v(ptr->val);
		JRB ptr2;
		jrb_traverse(ptr2, tree) {
			v2 = jval_i(ptr2->key);
			printf(" v2: '%s' (w = %2.f)",get_vertex_name(graph, v2), 
				get_edge_weight(graph, v, v2));
		}
		printf("\n");
	}
}

void topological_sort(Graph graph, void (*visit)(int))
{
	JRB ptr;
	int V = 0;
	jrb_traverse(ptr, graph.vertices) {
		V++;
	}
	int indegree_node[V];
	int indegree_arr[V];

	Dllist queue = new_dllist();
	jrb_traverse(ptr, graph.vertices) {
		int key = jval_i(ptr->key);
		indegree_arr[key] = in_degree(graph, key, indegree_node);
		if(indegree_arr[key] == 0)
			dll_append(queue, new_jval_i(key));
	}
	// Traversing
	while(dll_empty(queue) != 1) {
		// Take first element in the queue
		Dllist node = dll_first(queue);
		int key = jval_i(node->val);
			// Dequeue this element
		dll_delete_node(node);

		visit(key);
		int outdegree_node[V];

		int count = out_degree(graph, key, outdegree_node);
		for (int i = 0; i < count; ++i)	{
			int tail = outdegree_node[i];
			indegree_arr[tail]--;
			if (indegree_arr[tail] == 0) {
				dll_append(queue, new_jval_i(tail));
			}
		}	
	}
	free_dllist(queue);
}

void topological_sort_t(Graph g, int *output, int *n) {
	JRB node;
	int indegreeList[100];
	int adjacents[100];
	int count = 0;
	int i, total;
	int key;
	int tail;
	Dllist queue = new_dllist();
	Dllist temp;

	jrb_traverse(node, g.vertices) {
		indegreeList[count] = in_degree(g, jval_i(node->key), adjacents);
		if (indegreeList[count] == 0) {
			dll_append(queue, node->key);
		}
		count++;
	}

	*n = count;
	count = 0;
    // indegreeList
    // 0, 1, 1, 1, 2, 0
    // -1, 0, 0, 1, 1, 0

	while(dll_empty(queue) != 1) {
		temp = dll_first(queue);
		key = jval_i(temp->val);
		dll_delete_node(temp);

		output[count] = key;
		indegreeList[key] = -1;

		total = out_degree(g, key, adjacents);
		for (i = 0; i < total; i++) {
			tail = adjacents[i];
			indegreeList[tail]--;
			if (indegreeList[tail] == 0) {
				dll_append(queue, new_jval_i(tail));
			}
		}

		count++;
	}
}

void topologicalSort_no_counti(Graph g, int * output, int * n) {// ok
	JRB node;
	JRB indegreeList = make_jrb();
	int adjacents[100];
	int count = 0;
	int i, total;
	int key;
	int tail;
	Dllist queue = new_dllist();
	Dllist temp;

	jrb_traverse(node, g.vertices) {
    	// temp value
		int node_key = jval_i(node->key);
		int node_inDegree = in_degree(g, node_key, adjacents);
        ///
		jrb_insert_int(indegreeList, node_key, new_jval_i(node_inDegree));
		if (node_inDegree == 0) {
			dll_append(queue, node->key);
		}
		count++;
	}
	// jrb_traverse(node, indegreeList) {
	// 	printf("id: %d val: %d\n", jval_i(node->key), jval_i(node->val));
	// }
	*n = count;
	count = 0;
    // indegreeList
    // 0, 1, 1, 1, 2, 0
    // -1, 0, 0, 1, 1, 0/

	while(dll_empty(queue) != 1) {
		temp = dll_first(queue);
		key = jval_i(temp->val);
		dll_delete_node(temp);

		output[count] = key;
		node = jrb_find_int(indegreeList, key);
		if(node != NULL) {
			jrb_delete_node(node);
			jrb_insert_int(indegreeList, key, new_jval_i(-1));
		}


		total = out_degree(g, key, adjacents);
		for (i = 0; i < total; i++) {
			tail = adjacents[i];
			node = jrb_find_int(indegreeList, tail);
			if (node != NULL) {
				int tail_indegree = jval_i(node->val);
				jrb_delete_node(node);
				tail_indegree--;
				jrb_insert_int(indegreeList, tail, new_jval_i(tail_indegree));
				if (tail_indegree == 0) {
					dll_append(queue, new_jval_i(tail));
				}
			}
		}
		count++;
		// printf("=================\n");
		// jrb_traverse(node, indegreeList) {
		// 	printf("id: %d val: %d\n", jval_i(node->key), jval_i(node->val));
		// }
	}
}


// never used
int count_adjacent(Graph G, int v){
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	int count = 0;
	jrb_traverse(node, tree)
		count++;
	return count;
}

int _cmp_count_adjacent_asc(const void *v1, const void *v2){
	int a1, a2;
	a1 = count_adjacent(_G, *(int*)v1);
	a2 = count_adjacent(_G, *(int*)v2);
	if (a1 > a2)
		return 1;
	else if (a1 < a2)
		return -1;
	return 0;
}

void get_vertices_sorted_by_adjacent(Graph G, int *output){
	get_vertices_id(G, output);
	_G = G;
	qsort(output, count_vertices(G), sizeof(int), _cmp_count_adjacent_asc);
}

void drop_graph(Graph *G)
{
	JRB node;
	jrb_traverse(node, G->edges)
		jrb_free_tree(jval_v(node->val));
	jrb_free_tree(G->vertices);
	jrb_free_tree(G->edges);
}

