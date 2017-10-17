#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"
#include "../../lib/libfdr/jrb.h"
#include "../../lib/libfdr/dllist.h"

Graph createGraph()
{
	return make_jrb();
}

int isAdjacent(Graph g, int v1, int v2)
{
	if (g == NULL) return 0;

	Graph node = jrb_find_int(g, v1);
	if (node != NULL) {

        Graph tree = (Graph)jval_v(node->val);                         
        Graph result = jrb_find_int(tree, v2);
        if(result != NULL)
            return 1;
    }
    return 0;
}


void addEdge(Graph g, int v1, int v2)
{
    Graph node;
    Graph tree;

	if(isAdjacent(g, v1, v2))
        return;

    node = jrb_find_int(g, v1);
    if (node == NULL) {
    	tree = make_jrb();
    	jrb_insert_int(g, v1, new_jval_v(tree));
    	jrb_insert_int(tree, v2, new_jval_i(1));
    } else {
    	tree = (Graph)jval_v(node->val);
    	jrb_insert_int(tree, v2, new_jval_i(1));
    }

    node = jrb_find_int(g, v2);
    if (node == NULL) {
    	tree = make_jrb();
    	jrb_insert_int(g, v2, new_jval_v(tree));
    	jrb_insert_int(tree, v1, new_jval_i(1));
    } else {
    	tree = (Graph)jval_v(node->val);
    	jrb_insert_int(tree, v1, new_jval_i(1));
    }
}



int getAdjacentVertices(Graph g, int V, int* output)
{
	if(g == NULL)
        return 0;

	int count = 0;
	Graph node = jrb_find_int(g, V);
	if (node != NULL) {
		Graph tree = (Graph)jval_v(node->val);
		Graph tmp = NULL;
		jrb_traverse(tmp, tree) {			
			output[count++] = jval_i(tmp->key);
		}
	}
	return count;
}

void dropGraph(Graph g)
{
	Graph tmp;
	jrb_traverse(tmp, g) {
		jrb_free_tree(jval_v(tmp->val));
    }
    jrb_free_tree(g);
}

void printGraph(Graph g, void (*func)(int))
{
    Graph ptr;
    jrb_traverse(ptr, g) {
        func(jval_i(ptr->key));
        printf(": ");
        Graph tree = (Graph) jval_v(ptr->val);
        Graph ptr2;
        jrb_traverse(ptr2, tree) {
            func(jval_i(ptr2->key));
        }
        printf("\n");
    }
}

void BFS(Graph g,int start,int stop,void(*func)(int))
{
	
	JRB check1 = jrb_find_int(g,start);
	JRB check2 = jrb_find_int(g,stop);
	if(check1 == NULL ) {
		printf("Graph does not have vertex %d\n", start);
    	return;
	}
	if(stop != -1 && check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
    	return;
	}
	// Create a graph name 'visited' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // visited (1) or not (0)
	Graph visited = createGraph();
	Graph tmp;
	int V = 0;
	jrb_traverse(tmp,g) {
		V++;
		jrb_insert_int(visited, jval_i(tmp->key), new_jval_i(0));
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

		tmp = jrb_find_int(visited, key);
		if(jval_i(tmp->val) == 0) {
			// Pass the vertex to external function
			func(key);
			// Mark this element as 'visited'
			jrb_delete_node(tmp);
			jrb_insert_int(visited, key, new_jval_i(1));
		}
		// If this is the required vertex, return
		if(key == stop) {
			return;
		}
      
		int count = getAdjacentVertices(g, key, output);
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

void DFS(Graph g, int start, int stop, void (*func)(int))
{

	JRB check1 = jrb_find_int(g,start);
	JRB check2 = jrb_find_int(g,stop);
	if(check1 == NULL ) {
		printf("Graph does not have vertex %d\n", start);
    	return;
	}
	if(stop != -1 && check2 == NULL) {
		printf("Graph does not have vertex %d\n", stop);
    	return;
	}
	
	// Create a graph name 'visited' in which each node's key is
    // a vertex, and it's key indicate whether the vertex has been
    // visited (1) or not (0)
    Graph visited = createGraph();
    Graph tmp;
    int V = 0;
    jrb_traverse(tmp, g) {
    	V++;
        jrb_insert_int(visited, jval_i(tmp->key), new_jval_i(0));
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
        // Pop this element
        dll_delete_node(dll_tmp);

        tmp = jrb_find_int(visited, key);
        if(jval_i(tmp->val) == 0) {
        	// Pass the vertex to external function
	        func(key);
	        // Mark this element as 'visited'
	        jrb_delete_node(tmp);
	        jrb_insert_int(visited, key, new_jval_i(1));
        }
        
        // If this is the required vertex, return
        if (key == stop) {
            return;
        }

        // JRB u_node = jrb_find_int(g, key);
		// if(u_node == NULL) continue;

		// JRB v_connect_to_u = (JRB)jval_v(u_node->val);
		// jrb_rtraverse(tmp, v_connect_to_u) {
		// 	JRB ptr = jrb_find_int(visited, tmp->key.i);
		// 	if(jval_i(ptr->val) == 0)
		// 		dll_append(stack, new_jval_i(tmp->key.i));
		// }

        
        int count = getAdjacentVertices(g, key, output);
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