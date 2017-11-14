#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "graph_weighted_jrb.h"
#include "../../lib/include/dllist.h"

void show_int(int num)
{
	printf("%4d ", num);
}
double shortestPath_T(Graph_W g, int s, int t, int * path, int * length);
int main(int argc, char const *argv[])
{

	Graph_W g = createGraph();
    addVertex(g, 0, "s");
    addVertex(g, 1, "t");
    addVertex(g, 2, "2");
    addVertex(g, 3, "3");
    addVertex(g, 4, "4");
    addVertex(g, 5, "5");
    addVertex(g, 6, "6");
    addVertex(g, 7, "7");
    addEdge(g, 0, 2, 9);
    addEdge(g, 0, 6, 14);
    addEdge(g, 0, 7, 15);
    addEdge(g, 2, 3, 24);
    addEdge(g, 3, 1, 19);
    addEdge(g, 3, 5, 2);
    addEdge(g, 4, 1, 6);
    addEdge(g, 4, 3, 6);
    addEdge(g, 5, 1, 16);
    addEdge(g, 5, 4, 11);
    addEdge(g, 6, 3, 18);
    addEdge(g, 6, 5, 30);
    addEdge(g, 6, 7, 5);
    addEdge(g, 7, 1, 44);
    addEdge(g, 7, 5, 20);

    int s = 0;
    int t = 1;
    int path[100];
    int length;
    double weight = shortestPath_T(g, s, t, path, &length);
    if (weight == INFINITIVE_VALUE) {
        printf("There is no path between %d and %d\n", s, t);
    } else {
        printf("Path between %d and %d: ", s, t);
        for (int i = 0; i < length; i++) {
            printf("%4d", path[i]);
        }
        printf("\nTotal weight: %.0f\n", weight);
    }

    dropGraph(g);
	return 0;
}

double shortestPath_T(Graph_W g, int s, int t, int * path, int * length) {
    JRB node = jrb_find_int(g.vertices, s);
    JRB distance = make_jrb();
    JRB parent = make_jrb();
    Dllist queue = new_dllist();
    int count = 0;

    // Return if the first or last node is not valid
    if (node == NULL) {
        return INFINITIVE_VALUE;
    }
    node = jrb_find_int(g.vertices, t);
    if (node == NULL) {
        return INFINITIVE_VALUE;
    }

    // We maintain two informations about each node:
    // the parent node (the node it come from) and the distance from the starting node
    // by traversing through the parent node
    jrb_traverse(node, g.vertices) {
        int key = jval_i(node->key);
        double dist = INFINITIVE_VALUE;
        if (key == s) {
            dist = 0;
        }
        // At first, all node does not have a parent, and its distance will be set to INFINITIVE_VALUE,
        // except for the starting node
        jrb_insert_int(distance, key, new_jval_d(dist));
        jrb_insert_int(parent, key, new_jval_i(-1));
    }

    // Create a priority queue, it which the order is determined by the distance to that node from the starting node
    // At first, the starting node will be the first element, since its distance would be 0, and the rest is INFINITIVE_VALUE
    jrb_traverse(node, g.vertices) {
        int key = jval_i(node->key);
        if (key == s) {
            dll_prepend(queue, new_jval_i(key));
        } else {
            dll_append(queue, new_jval_i(key));
        }
    }

    while(dll_empty(queue) != 1) {
        Dllist temp = dll_first(queue);
        int key = jval_i(temp->val);
        int adjacents[100];
        int i, total;
        int weight, toKey, toAdj;
        int adjKey;

        // If the first element in the queue is the node we are looking for,
        // that mean the path we took to it is shortest
        if (key == t) {
            i = total = 0;
            // Look up all the node in JRB parent
            while(key != -1) {
                // Use adjacents[] as a middle array,
                // since the way we traverse will return the
                // node in reverse order
                adjacents[total] = key;
                total++;
                key = jval_i(jrb_find_int(parent, key)->val);
            }
            // Return the correct path order
            for (i = 0; i < total; i++) {
                path[i] = adjacents[total - 1 - i];
            }
            // Return the total number of node in the route
            *length = total;
            // Return the total weight;  
            return jval_d(jrb_find_int(distance, t)->val);
        }

        // Dequeue the first element
        dll_delete_node(temp);

        // The distance to it from the start node
        toKey = jval_d(jrb_find_int(distance, key)->val);

        total = outDegree(g, key, adjacents);
        for (i = 0; i < total; i++) {
            adjKey = adjacents[i];
            weight = getEdgeValue(g, key, adjKey);
            toAdj = jval_d(jrb_find_int(distance, adjKey)->val);
            
            // If the path to the adjacent node can be shorten
            // by going through the current node,
            // we set its parent to the current node
            if (toKey + weight < toAdj) {
                // Set new distance
                toAdj = toKey + weight;
                node = jrb_find_int(distance, adjKey);
                jrb_delete_node(node);
                jrb_insert_int(distance, adjKey, new_jval_d(toAdj));
                
                // Set new parent
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
                    int dist = jval_d(jrb_find_int(distance, qKey)->val);
                    if (dist > toAdj) {
                        dll_insert_b(temp, new_jval_i(adjKey));
                        break;
                    }
                }
            }
        }
    }
}