#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/include/dllist.h"
#include "graph_weighted_jrb.h"

Graph_W createGraph()
{
	Graph_W newGraph;
	newGraph.edges = make_jrb();
	newGraph.vertices = make_jrb();

	return newGraph;
}


void addVertex(Graph_W graph, int id, char *name)
{
	JRB node = jrb_find_int(graph.vertices, id);

	if (node == NULL) {
		jrb_insert_int(graph.vertices, id, new_jval_s(name));
	} else {
		printf("Vertex already existed!\n");
	}
}


char *getVertexName(Graph_W graph, int id)
{
	JRB node = jrb_find_int(graph.vertices, id);

	if (node != NULL)
		return jval_s(node->val);
	return NULL;
}


int isAdjacent(Graph_W graph, int v1, int v2)
{
	JRB node1, tree, node2;

	node1 = jrb_find_int(graph.edges, v1);
	if (node1 != NULL) {
		tree = (JRB) jval_v(node1->val);
		node2 = jrb_find_int(tree, v2);

		if (node2 != NULL) return 1;
	}

	return 0;
}


void addEdge(Graph_W graph, int v1, int v2, double weight)
{
	if (isAdjacent(graph, v1, v2)) return;

	JRB node1, tree;

	node1 = jrb_find_int(graph.edges, v1);
	if (node1 == NULL) {
		tree = make_jrb();
		jrb_insert_int(graph.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_d(weight));
	} else {
		tree = (JRB) jval_v(node1->val);
		jrb_insert_int(tree, v2, new_jval_d(weight));
	}
}

double getEdgeValue(Graph_W graph, int v1, int v2)
{
	JRB node1, tree, node2;

	node1 = jrb_find_int(graph.edges, v1);
	if (node1 != NULL) {
		tree = (JRB) jval_v(node1->val);
		node2 = jrb_find_int(tree, v2);
		if (node2 != NULL) return jval_d(node2->val);
	}

	return INFINITIVE_VALUE;
}


void dropGraph(Graph_W graph)
{
	JRB node;
	
	jrb_traverse(node, graph.edges) {
		jrb_free_tree(jval_v(node->val));
	}

	jrb_free_tree(graph.vertices);
	jrb_free_tree(graph.edges);
}


int outDegree(Graph_W graph, int v, int *outDegreeList)
{
	int count = 0;
	JRB node, tree;

	node = jrb_find_int(graph.edges, v);
	if (node != NULL) {
		tree = (JRB) jval_v(node->val);
		JRB ptr;
		jrb_traverse(ptr, tree) {
			outDegreeList[count++] = jval_i(ptr->key);
		}
	}

	return count;
}

int inDegree(Graph_W graph, int v, int* inDegreeList)
{
	int count = 0;

	JRB node;

	node = jrb_find_int(graph.vertices, v);
	if (node != NULL) {
		JRB ptr;
		jrb_traverse(ptr, graph.vertices) {
			int inVertex = jval_i(ptr->key);
			if (isAdjacent(graph, inVertex, v))
				inDegreeList[count++] = inVertex;
		}
	}

	return count;
}

double shortestPath(Graph_W graph, int start, int stop, int *path, int *length)
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
		return INFINITIVE_VALUE;
	}
	if (check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
		return INFINITIVE_VALUE;
	}

	// We maintain two informations about each node:
    // the parent node (the node it come from) and the distance from the sing node
    // by traversing through the parent node
    int V = 0;
	jrb_traverse(node, graph.vertices) {
		int key = jval_i(node->key);
		double dist = INFINITIVE_VALUE;
		if (key == start) {
			dist = 0;
		}
		// At first, all node does not have a parent, and its distance will be set to INFINITIVE_VALUE,
        // except for the sing node
		jrb_insert_int(distance, key, new_jval_d(dist));
		jrb_insert_int(parent, key, new_jval_i(-1));
		V++;
	}

	// Create a priority queue, it which the order is determined by the distance to that node from the sing node
    // At first, the sing node will be the first element, since its distance would be 0, and the rest is INFINITIVE_VALUE
	
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

		int count = outDegree(graph, key, adjacents);
		for (int i = 0; i < count; i++) {
			int adjKey = adjacents[i];
			double weight = getEdgeValue(graph, key, adjKey);
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
						dll_insert_b(temp, new_jval_i(adjKey));
						break;
					}
				}
			}
		}
	}
	free_dllist(queue);
	jrb_free_tree(parent);
	jrb_free_tree(distance);
	return INFINITIVE_VALUE;
}