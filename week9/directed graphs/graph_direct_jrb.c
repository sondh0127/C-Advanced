#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_direct_jrb.h"
#include "../../lib/include/dllist.h"

Graph_D createGraph()
{
	Graph_D newGraph;
	newGraph.edges = make_jrb();
	newGraph.vertices = make_jrb();
	return newGraph;
}

void dropGraph(Graph_D graph)
{
	JRB ptr;
	jrb_traverse(ptr, graph.edges) {
		jrb_free_tree(jval_v(ptr->val));
	}
	jrb_free_tree(graph.vertices);
	jrb_free_tree(graph.edges);
}

void addVertex(Graph_D graph, int id, char *name)
{
	JRB tmp = jrb_find_int(graph.vertices, id);
	if (tmp == NULL) {
		jrb_insert_int(graph.vertices, id, new_jval_s(name));
	} else {
		printf("Vertex already existed!\n");
	}
}

char *getVertex(Graph_D graph, int id)
{
	JRB tmp = jrb_find_int(graph.vertices, id);
	if(tmp != NULL)
		return jval_s(tmp->val);
	return NULL;
}

int isAdjacent(Graph_D graph, int v1, int v2)
{
	if (graph.edges == NULL) return 0;

	JRB tmp = jrb_find_int(graph.edges, v1);
	if (tmp != NULL) {
		JRB tree = (JRB) jval_v(tmp->val);
		JRB status = jrb_find_int(tree, v2);
		if(status != NULL)
			return 1;
	}
	return 0;
}

void addEdge(Graph_D graph, int v1, int v2)
{
	if (isAdjacent(graph, v1, v2)) return;
	JRB tmp = jrb_find_int(graph.edges, v1);
	JRB tree; // represent an adjacency list node
	if (tmp == NULL) {
		tree = make_jrb();
		jrb_insert_int(graph.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_i(1));
	} else {
		tree = (JRB)jval_v(tmp->val);
		jrb_insert_int(tree, v2, new_jval_i(1));
	}
}

int outDegree(Graph_D graph, int v, int *output)
{
	if (graph.edges == NULL) return 0;

	int count = 0;
	JRB tmp = jrb_find_int(graph.edges, v);
	
	if (tmp != NULL) {
		JRB ptr;
		JRB tree = (JRB)jval_v(tmp->val);
		jrb_traverse(ptr, tree) {
			output[count++] = jval_i(ptr->key);
		}
	}
	return count;
}

// outDegree
// inDegree
int inDegree(Graph_D graph, int v, int* output)
{ 	// return the size of adjec, and adjacent into output
	if (graph.vertices == NULL) return 0;

	int count = 0;
	JRB tmp = jrb_find_int(graph.vertices, v);
	if (tmp != NULL) {
		JRB ptr;
		jrb_traverse(ptr, graph.vertices) {
			if(isAdjacent(graph, jval_i(ptr->key), v))
				output[count++] = jval_i(ptr->key);
		}
	}
	return count;
}


void BFS(Graph_D graph,int start,int stop,void(*func)(int))
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
	// Create a Graph name 'visited' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // visited (1) or not (0)
	JRB visited = make_jrb();
	JRB ptr;
	int V = 0;
	jrb_traverse(ptr,graph.vertices) {
		V++;
		jrb_insert_int(visited, jval_i(ptr->key), new_jval_i(0));
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
		
		JRB tmp = jrb_find_int(visited, key);
		if(jval_i(tmp->val) == 0) {
			// Pass the vertex to external function
			func(key);
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
		
		int count = outDegree(graph, key, output);
		for (int i = 0; i < count; i++)
		{
			JRB ptr = jrb_find_int(visited, output[i]);
			if(jval_i(ptr->val) == 0)
				dll_append(queue,new_jval_i(output[i])); 
		}

	}
	free_dllist(queue);
	jrb_free_tree(visited);
}

// DFS ..........................................................

void DFS(Graph_D graph, int start, int stop, void (*func)(int))
{

	JRB check1 = jrb_find_int(graph.vertices,start);
	JRB check2 = jrb_find_int(graph.vertices,stop);
	if(check1 == NULL ) {
		printf("Graph_D does not have vertex %d\n", start);
		return;
	}
	if(stop != -1 && check2 == NULL) {
		printf("Graph_D does not have vertex %d\n", stop);
		return;
	}
	
	// Create a Graph_D name 'visited' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // visited (1) or not (0)
	JRB visited = make_jrb();
	JRB ptr;
	int V = 0;
	jrb_traverse(ptr, graph.vertices) {
		V++;
		jrb_insert_int(visited, jval_i(ptr->key), new_jval_i(0));
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

		JRB tmp = jrb_find_int(visited, key);
		if(jval_i(tmp->val) == 0) {
        	// Pass the vertex to external function
			func(key);
	        // Mark this element as 'visited'
			jrb_delete_node(tmp);
			jrb_insert_int(visited, key, new_jval_i(1));
		} else {
			// Pop this element
			dll_delete_node(dll_tmp);
		}

		// If this is the required vertex, return
		if (key == stop) {
			free_dllist(stack);
			jrb_free_tree(visited);
			return;
		}

		int count = outDegree(graph, key, output);
		for (int i = count -1 ; i >= 0; i--)
		{
	            // If the vertice has not been visited, push it
			tmp = jrb_find_int(visited, output[i]);
			if (jval_i(tmp->val) == 0) {
				key = jval_i(tmp->key);
				dll_append(stack, new_jval_i(key));
			}
		}
	}
	free_dllist(stack);
	jrb_free_tree(visited);
}


int isCycleVertex(Graph_D graph, int start)
{
	JRB visited = make_jrb();
	JRB ptr;
	int V = 0;
	jrb_traverse(ptr, graph.vertices) {
		V++;
		jrb_insert_int(visited, jval_i(ptr->key), new_jval_i(0));
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

		JRB tmp = jrb_find_int(visited, key);
		if(jval_i(tmp->val) == 0) {
        	// Pass the vertex to external function
			//printf("%4d ", key);
	        // Mark this element as 'visited'
			jrb_delete_node(tmp);
			jrb_insert_int(visited, key, new_jval_i(1));
		} else {
			// Pop this element
			dll_delete_node(dll_tmp);
		}
		int count = outDegree(graph, key, output);
		for (int i = count -1 ; i >= 0; i--) {
			if (start == output[i])
			{
				jrb_free_tree(visited);
				free_dllist(stack);
				return 1;
			}
			// If the vertice has not been visited, push it
			tmp = jrb_find_int(visited, output[i]);
			if (jval_i(tmp->val) == 0) {
				key = jval_i(tmp->key);
				dll_append(stack, new_jval_i(key));
			}
		}
	}
	
	free_dllist(stack);
	jrb_free_tree(visited);
	return 0;
}

int isCycle(Graph_D graph)
{	
	JRB ptr;
	jrb_traverse(ptr,graph.edges) {
		if(isCycleVertex(graph,jval_i(ptr->key)) == 1)
			return 1;
	}
	return 0;
}

void showVertices(Graph_D graph)
{
	JRB ptr;
	jrb_traverse(ptr, graph.vertices) {
		printf("%d - \"%s\"\n", jval_i(ptr->key), jval_s(ptr->val));
	}
}

void printGraph(Graph_D graph)
{
	JRB ptr;	
	jrb_traverse(ptr, graph.edges) {
		printf("%s: ", getVertex(graph, jval_i(ptr->key)));
		JRB tree = (JRB) jval_v(ptr->val);
		JRB ptr2;
		jrb_traverse(ptr2, tree) {
			printf("%4s",getVertex(graph, jval_i(ptr2->key)));
		}
		printf("\n");
	}
}

void topologicalSort(Graph_D graph, void (*visit)(int))
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
 		indegree_arr[key] = inDegree(graph, key, indegree_node);
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

 		int count = outDegree(graph, key, outdegree_node);
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

 void topologicalSort_T(Graph_D g, int * output, int * n) {
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
        indegreeList[count] = inDegree(g, jval_i(node->key), adjacents);
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

        total = outDegree(g, key, adjacents);
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