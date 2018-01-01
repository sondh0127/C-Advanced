#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

Graph create_graph() {
	Graph G;
	G.vertices = make_jrb();
	G.edges = make_jrb();
	return G;
}

void add_vertex(Graph G, int id, char *name){
	assert(G.vertices);
	JRB node = jrb_find_int(G.vertices, id);
	if (node == NULL)
		jrb_insert_int(G.vertices, id, new_jval_s(name));
}

void add_vertex_auto_increment(Graph G, char *name){
	assert(G.vertices);
	if(get_vertex_id(G, name) != UNDEFINED)
		return;
	int v = get_graph_max_id(G) + 1;
	add_vertex(G, v, name);
}

char *get_vertex_val(Graph G, int id) {
	JRB node = jrb_find_int(G.vertices, id);
	if (node != NULL)
		return jval_s(node->val);
	return NULL;
}

int get_vertex_id(Graph G, char *name){
	JRB node, tree;
	tree = G.vertices;
	jrb_traverse(node, tree)
		if(!strcmp(name, jval_s(node->val)))
			return jval_i(node->key);
	return UNDEFINED;
}

int get_vertices_id(Graph G, int *output){
	JRB node;
	int total=0;
	jrb_traverse(node, G.vertices)
		output[total++] = jval_i(node->key);
	return total;
}

int count_vertices(Graph G){
	JRB node, tree;
	tree = G.vertices;
	int count = 0;
	jrb_traverse(node, tree)
		count++;
	return count;
}

void _add_edge(Graph G, int v, int v2, double weight){
	assert(G.edges);
	if (has_edge(G, v, v2)){
		return;	
	}
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if(node == NULL){
		tree = make_jrb();
		jrb_insert_int(G.edges, v, new_jval_v(tree));
	}
	else
		tree = (JRB) jval_v(node->val);
	jrb_insert_int(tree, v2, new_jval_d(weight));	
}

void add_edge(Graph G, int v, int v2, double weight, short mode){
	_add_edge(G, v, v2, weight);
	if(mode == UNDIRECTED){
		_add_edge(G, v2, v, weight);
	}
}

int has_edge(Graph G, int v, int v2) {
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if (node == NULL)
		return false;
	tree = (JRB) jval_v(node->val);
	JRB f = jrb_find_int(tree, v2);
	if (f != NULL)
		return true;
	return false;
}

double get_edge_weight(Graph G, int v, int v2) {
	if (v == v2)
		if (!has_edge(G, v, v2))
			return 0;
	else
		if (!has_edge(G, v, v2))
			return INFINITY;
	JRB node = jrb_find_int(G.edges, v);
	JRB tree = (JRB) jval_v(node->val);
	JRB f = jrb_find_int(tree, v2);
	return jval_d(f->val);
}

int count_edges(Graph G, short mode){
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

int is_adjacent(Graph G, int v, int v2){
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

int get_adjacent_vertices_out_edge(Graph G, int v, int *output){
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree){
		output[total++] = jval_i(node->key);		
	}
	return total;
}

int get_adjacent_vertices_in_edge(Graph G, int v2, int *output){
	JRB node_v;
	int v;
	int total = 0;
	jrb_traverse(node_v, G.vertices){
		v = jval_i(node_v->key);
		if(is_adjacent(G, v, v2)){
			output[total++] = v;
		}
	}
	return total;
}

int get_adjacent_vertices(Graph G, int v, int *output){
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if(node == NULL)
		return false;
	tree = (JRB) jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree){
		output[total++] = jval_i(node->key);		
	}
	return total;
}

int count_adjacent(Graph G, int v){
	JRB node = jrb_find_int(G.edges, v);
	JRB tree;
	if(node == NULL)
		return false;
	tree = (JRB) jval_v(node->val);
	int count = 0;
	jrb_traverse(node, tree)
		count++;
	return count;
}

int out_degree(Graph G, int v, int *output) {
	JRB node = jrb_find_int(G.edges, v);
	if (node == NULL)
		return false;
	int total = 0;
	JRB tree;
	tree = (JRB) jval_v(node->val);
	jrb_traverse(node, tree)
		output[total++] = jval_i(node->key);
	return total;
}

int in_degree(Graph G, int v, int *output) {
	JRB node = jrb_find_int(G.vertices, v);
	if (node == NULL)
		return false;
	int total = 0;
	jrb_traverse(node, G.vertices) {
		if (has_edge(G, jval_i(node->key), v))
			output[total++] = jval_i(node->key);
	}
	return total;
}

void drop_graph(Graph *G) {
	JRB node;
	jrb_traverse(node, G->edges)
		jrb_free_tree(jval_v(node->val));
	jrb_free_tree(G->vertices);
	jrb_free_tree(G->edges);
}

void bfs(Graph G, int start, int stop, void (*visited_func)(Graph, int)){
	JRB tmp;
	int max_id = get_graph_max_id(G);
	int *visited = (int*)malloc((max_id + 1) * sizeof(int));
	if (visited == NULL) {
		fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
		exit(1);
	}

	JRB node;
	jrb_traverse(node, G.vertices)
		visited[jval_i(node->key)] = 0;

	Dllist queue = new_dllist();

	node = jrb_find_int(G.vertices, start);
	if (node == NULL)
		goto end;
	dll_append(queue, new_jval_i(start));

	while (!dll_empty(queue)) {
		Dllist node = dll_first(queue);
		int u = jval_i(node->val);
		dll_delete_node(node);

		if (!visited[u]) {
		visited_func(G, u);
		visited[u] = 1;
		}

		if (u == stop)
			goto end;

		JRB u_node = jrb_find_int(G.edges, u);
		if (u_node == NULL)
			continue;

		JRB vertex_connect_to_u_tree = (JRB)(jval_v(u_node->val));

		jrb_traverse(tmp, vertex_connect_to_u_tree)
			if (!visited[tmp->key.i])
				dll_append(queue, new_jval_i(tmp->key.i));
	}
	end:
		free(visited);
		free_dllist(queue);
}

void dfs(Graph G,  int start, int stop, void (*visited_func)(Graph, int)) {
	JRB tmp;
	int max_id = get_graph_max_id(G);

	int *visited = (int*)malloc((max_id + 1) * sizeof(int));
		if (visited == NULL) {
		fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
		exit(1);
	}

	JRB node;
	jrb_traverse(node, G.vertices)
		visited[jval_i(node->key)] = 0;
	Dllist stack = new_dllist();

	node = jrb_find_int(G.edges, start);
	if (node == NULL)
		goto end;
	dll_append(stack, new_jval_i(start));

	while (!dll_empty(stack)) {
		Dllist node = dll_last(stack);
		int u = jval_i(node->val);
		dll_delete_node(node);

		if (!visited[u]) {
			visited_func(G, u);
			visited[u] = 1;
		}

		if (u == stop)
			goto end;

		JRB u_node = jrb_find_int(G.edges, u);
		if (u_node == NULL)
			continue;

		JRB vertex_connect_to_u_tree = (JRB)(jval_v(u_node->val));


		jrb_rtraverse(tmp, vertex_connect_to_u_tree)
			if (!visited[tmp->key.i])
				dll_append(stack, new_jval_i(tmp->key.i));
	}

	end:
	free(visited);
	free_dllist(stack);
}

int get_graph_max_id(Graph G) {
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

int get_graph_min_id(Graph G) {
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

int _is_cyclic(Graph G, int start) {
	int max_id = get_graph_max_id(G);

	int *visited = (int*)malloc((max_id + 1) * sizeof(int));
	if (visited == NULL) {
		fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
		exit(1);
	}

	JRB node;
	jrb_traverse(node, G.vertices)
		visited[jval_i(node->key)] = 0;

	Dllist stack = new_dllist();

	// add start node to stack
	node = jrb_find_int(G.vertices, start);
	if (node == NULL)
		goto end;
	dll_append(stack, new_jval_i(start));

	int flag = 0;

	while (!dll_empty(stack)) {
		Dllist node = dll_last(stack);
		int u = jval_i(node->val);
		dll_delete_node(node);

		if (!visited[u]) {
			visited[u] = 1;
			if (!flag && (u == start))
				visited[u] = 0;
		}
		if ((u == start) && (visited[start] == 1)) {
			free(visited);
			free_dllist(stack);
			return true;
		}
		flag++;
		JRB u_node = jrb_find_int(G.vertices, u);
		if (u_node == NULL)
			continue;
		int *out_degree_u_list = malloc((max_id + 1) * sizeof(int));
		int out_degree_u;
		if(out_degree_u_list == NULL){
			fprintf(stderr, "%s %s:%d\n", "malloc failed in", __FILE__, __LINE__);
			exit(1);
		}

		if ((out_degree_u = out_degree(G, u, out_degree_u_list)) == 0)
			continue;

		int i;
		for(i = 0; i < out_degree_u; i++){
			int _v = out_degree_u_list[i];
			if (!visited[_v])
			dll_append(stack, new_jval_i(_v));
		}

		free(out_degree_u_list);
	}
	end:
		free(visited);
		free_dllist(stack);
		return false;
}

int is_cyclic(Graph G) {
	if (G.edges == NULL || G.vertices == NULL)
		return false;
	JRB tmp;
	jrb_traverse(tmp, G.vertices) {
		if (_is_cyclic(G, jval_i(tmp->key)))
		return true;
	}
	return false;
}

void topological_sort(Graph G, void (*visited_func)(Graph, int)) {
	Dllist queue = new_dllist();
	JRB tmp;

	JRB node = jrb_find_int(G.vertices, get_graph_min_id(G));
	if (node == NULL)
		goto end;

	int max_id = get_graph_max_id(G);
	int *in_degree_node = malloc(sizeof(int) * (max_id + 1));
	if (in_degree_node == NULL) {
		fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
		exit(1);
	}

	int *in_degree_arr = malloc(sizeof(int) * (max_id + 1));
	if (in_degree_arr == NULL) {
		fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
		exit(1);
	}

	jrb_traverse(tmp, G.vertices) {
		int v = jval_i(tmp->key);
		if ((in_degree_arr[v] = in_degree(G, v, in_degree_node)) == 0) {
			dll_append(queue, new_jval_i(v));
		}
	}

	free(in_degree_node);
	while (!dll_empty(queue)) {
		Dllist node = dll_first(queue);
		int u = jval_i(node->val);
		dll_delete_node(node);

		visited_func(G, u);

		int *out_degree_node_u = malloc(sizeof(int) * (max_id + 1));
		if (out_degree_node_u == NULL) {
			fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
			exit(1);
		}

		int out_degree_u;
		if ((out_degree_u = out_degree(G, u, out_degree_node_u)) != 0) {
			int w, i;
			int *in_degree_node_w = malloc(sizeof(int) * (max_id + 1));
			if (in_degree_node_w == NULL) {
				fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
				exit(1);
			}
			for (i = 0; i < out_degree_u; ++i){
				w = out_degree_node_u[i];
				in_degree_arr[w] -= 1;

				if (in_degree_arr[w] == 0)
					dll_append(queue, new_jval_i(w));
			}
			free(in_degree_node_w);
		}
		free(out_degree_node_u);
	}

	end:
		free(in_degree_arr);
		free_dllist(queue);
}

double shortest_path(Graph G, int s, int t, int* path, double* length) {
	if (path == NULL || length == NULL){
		log("path or length are null");
		return INFINITY;		
	}

	if (s==t)
		return 0;

	int i, max_id = get_graph_max_id(G);
	int min_id = get_graph_min_id(G);

	if (t > max_id || s > max_id || t < min_id || s < min_id){
		log("node not in graph");
		*length = 0;
		return INFINITY;		
	}

	double *dist = malloc(sizeof(double) * (max_id + 1));  // free ?
	int *prev = malloc(sizeof(int) * (max_id + 1));
	if (!dist || !prev) {
		fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
		exit(1);
	}

	Dllist queue = new_dllist();   // free ?
	JRB node;
	jrb_traverse(node, G.vertices) {
		int u = jval_i(node->key);
		if (u != s) {
			dist[u] = INFINITY;
			prev[u] = UNDEFINED;
		}
		dll_append(queue, new_jval_i(u));
	}

	dist[s] = 0;

	while (!dll_empty(queue)) {
		// extract min
		int u;
		Dllist tmp, min_node = dll_first(queue);
		int min = jval_i(dll_first(queue)->val);
		dll_traverse(tmp, queue) {
			int tmp_node_i = jval_i(tmp->val);
			if (dist[min] > dist[tmp_node_i]) {
				min = tmp_node_i;
				min_node = tmp;
			}
		}
		u = min;
		dll_delete_node(min_node);
		//

		int *out_degree_u_list = malloc(sizeof(int) * (max_id + 1));  // free ?
		if (!out_degree_u_list) {
			fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
			exit(1);
		}
		int out_degree_u = out_degree(G, u, out_degree_u_list);
		if (out_degree_u == 0)
			continue;

		int i;
		for (i = 0; i < out_degree_u; i++) {
			int v = out_degree_u_list[i];
			double alt = dist[u] + get_edge_weight(G, u, v);
			if (alt < dist[v]) {
				dist[v] = alt;
				prev[v] = u;
				dll_append(queue, new_jval_i(v));
			}
		}
		free(out_degree_u_list);
	}

	for (i = min_id; i <= max_id; i++)
		length[i] = dist[i];

	if (prev[t] != -1) {
		int j = 1;
		path[0] = t;
		while (1) {
			path[j] = prev[path[j - 1]];
			if (path[j] == s || path[j] == -1)
			break;
			j++;
		}
		path[++j] = -1;
	}
	double ret = dist[t];

	free_dllist(queue);
	free(dist);
	free(prev);
	return ret;
}

Dllist _topological_queue;

void _get_topological_id(Graph G, int v){
	// log("%s->", get_vertex_val(G, v));
	dll_append(_topological_queue, new_jval_i(v));
}

void get_topological_queue(Graph G, int *output, int *length){
	// log("[lib] at get_topological_queue:\n");
	_topological_queue = new_dllist();
	topological_sort(G, _get_topological_id);
	int i, total=0;
	Dllist ptr;
	dll_traverse(ptr, _topological_queue)
		output[total++] = jval_i(ptr->val);
	free_dllist(_topological_queue);
	*length = total;
	// log("\n");
}

int count_prequisites(Graph G, int v){
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

double get_path_weight(Graph G, int *path, int total){
	int i, w, total_w=0;
	for(i=0; i<total-1; i++){
		w = get_edge_weight(G, path[i], path[i+1]);
		if(w == INFINITY)
			return INFINITY;
		total_w += w;
	}
	return total_w;
}

double get_path_weight_v2(Graph G, int *path){
	int i, w, total_w=0;
	for(i=0; path[i]>=0; i++){
		printf("%d\n", path[i]);
	}
	for(i=0; path[i+1]>= 0; i++){
		w = get_edge_weight(G, path[i+1], path[i]);
		if(w >= INFINITY-1)
			return INFINITY;
		total_w += w;
	}
	return total_w;
}

double topological_get_minimun_cost(Graph G, int v2){
	int *output, n, v, total;
	double *length;
	n = count_vertices(G);

	output = (int*)malloc(sizeof(int) * n);
	get_topological_queue(G, output, &total);
	v = output[0];
	free(output);

	output = (int*)malloc(sizeof(int) * n);
	length = (double*)malloc(sizeof(double) * 100);
	shortest_path(G, v, v2, output, length);
	free(length);
	free(output);
	return get_path_weight_v2(G, output);
}
