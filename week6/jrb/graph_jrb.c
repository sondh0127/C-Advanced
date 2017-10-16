#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"
#include "../../lib/libfdr/jrb.h"

Graph_JRB createGraph_JRB()
{
	Graph_JRB g = make_jrb();
	return g;
}

int isAdjacent(Graph_JRB g, int vertex_i, int vertex_j)
{
	if (g == NULL) 
		return 0;

	JRB node = jrb_find_int(g, vertex_i);
	if (node == NULL) return 0;

	JRB tree = (JRB)jval_v(node->val);                         
	JRB f = jrb_find_int(tree, vertex_j);
	if(f != NULL)
		return 1;
	return 0;
}


void addEdge(Graph_JRB g, int vertex_i, int vertex_j){
	if(isAdjacent(g, vertex_i, vertex_j))
        return;
    JRB node = jrb_find_int(g, vertex_i);
    if (node == NULL) {
    	JRB tree = make_jrb();
    	jrb_insert_int(g, vertex_i, new_jval_v(tree));
    	jrb_insert_int(tree, vertex_j, new_jval_i(1));
    } else {
    	JRB tree = (JRB)jval_v(node->val);
    	jrb_insert_int(tree, vertex_j, new_jval_i(1));
    }

    node = jrb_find_int(g, vertex_j);
    if (node == NULL) {
    	JRB tree = make_jrb();
    	jrb_insert_int(g, vertex_j, new_jval_v(tree));
    	jrb_insert_int(tree, vertex_i, new_jval_i(1));
    } else {
    	JRB tree = (JRB)jval_v(node->val);
    	jrb_insert_int(tree, vertex_i, new_jval_i(1));
    }
}



int getAdjacentVertices(Graph_JRB g, int vertex, int *output)
{
	if(g == NULL)
		return 0;

	int count = 0;
	JRB node = jrb_find_int(g, vertex);
	if (node != NULL) {
		JRB tree = (JRB)jval_v(node->val);
		JRB ptr = NULL;
		jrb_traverse(ptr, tree) {
			if(isAdjacent(g, vertex, jval_i(ptr->key))) {
				output[count++] = jval_i(ptr->key);
			}
		}
	}

	
	return count;
}
void dropGraph_JRB(Graph_JRB g)
{
	JRB ptr;
	jrb_traverse(ptr, g) {
		jrb_free_tree(jval_v(ptr->val));
 	}
    jrb_free_tree(g);
}

void printGraph_JRB(Graph_JRB g)
{
    
    JRB ptr;
    jrb_traverse(ptr, g) {
        printf("%2d: ", jval_i(ptr->key));
        JRB tree = (JRB) jval_v(ptr->val);
        JRB ptr2;
        jrb_traverse(ptr2, tree) {
            printf("%2d ", jval_i(ptr2->key));
        }
        printf("\n");
    }
}


