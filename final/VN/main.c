#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "graph.h"
#include "api.h"
#include "../../lib/include/dllist.h"
#include "../../lib/include/jrb.h"
#include "../../lib/include/fields.h"

// MAIN
int main(int argc, char *argv[])
{
    // Main variable
	Graph G;
	char fn[100] = "products.txt";
	char fn2[100] = "orderhistory.txt";
	
	// JRB node;
	char *name1, *name2;
	int v, v2;
	int total, *output;
	// Array1 *a;
	double weight;
	int flag, length;
	// double time;
    // --------------------------------
	int choose = 0;
	do {
		choose = menu();
		switch (choose) {
			case 1:
			// if (G.vertices || G.edges)
			// 	drop_graph(&G);
			G = create_graph();

			add_all_vertices(G, fn);
			
			log(" Import data success!\n");
			log(" Summary: \n");
			printf("	All products:\n");
			print_all_vertices(G);
			// printf("	- Number of \"vertices\": %d\n", count_vertices(G));
			// printf("	- Number of \"edges\": %d\n", count_edges(G, UNDIRECTED));
			// endinput:
			
			break;
			case 2:
			printf("	Order history: \n");
			add_all_edges(G, fn2);
			// print_graph(G);
			break;
			case 3:
			name1 = (char*) malloc(sizeof(char) * 10);
			name2 = (char*) malloc(sizeof(char) * 10);
			log(" Enter first product: ");
			readLn(stdin, name1, 10);
			v = atoi(name1);
			log(" Enter second product: ");
			readLn(stdin, name2, 10);
			v2 = atoi(name2);
			weight = get_edge_weight(G, v, v2);
			if (weight == INFINITY) {
				weight = -1 ;
			}
			printf("	Relevance between products: %.f ", weight);
			printf("	Related Products: %.f ", weight);
			break;
			// 
			case 4:
			name2 = (char*) malloc(sizeof(char) * 10);
			log(" Enter products member: ");
			readLn(stdin, name2, 10);
			v = atoi(name2);
			output = (int*) malloc(sizeof(int) * count_vertices(G));
			total = get_adjacent_sorted_by_weight(G, v, output);
			printf("	Related Products: ");
			for (int i = 0; i < total; i++) {
				printf("%s ", get_vertex_name(G, output[i]));
			}
			printf("\n");
			break;
			// 
			case 5:
			name1 = (char*) malloc(sizeof(char) * 10);
			name2 = (char*) malloc(sizeof(char) * 10);
			log(" Enter first product: ");
			readLn(stdin, name1, 10);
			v = atoi(name1);
			log(" Enter second product: ");
			readLn(stdin, name2, 10);
			v2 = atoi(name2);
			// flag  = is_adjacent(G, v, v2);
			// if (flag) {
			// 	printf("	Related Products: ");
			// 	dfs(G, v, v2, print_vertices_name);
			// } else {
			// 	printf("	- The two products are not related to each other\n");
			// }
			output = (int*) malloc(sizeof(int) * count_vertices(G));
			shortest_path(G, v, v2, output, &length);
			if (length < 2) printf("There is no path between these 2 products.\n");
			else {
				for (int i = 0; i < length; i++) {
					printf("%s", get_vertex_name(G, output[i]));
					if (i == length - 1) printf("\n");
					else printf(" - ");
				}
			}
			
			break;
			// 
			case 6:
			if (G.vertices || G.edges)
				drop_graph(&G);
			printf("	- Exited!\n");
			break;
			// 
			default:
			printf("	- Invalid input! Type (1-6)\n");
			break;  
		}
	}  while (choose != 6);
	return 0;
}