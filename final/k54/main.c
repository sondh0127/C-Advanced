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
	char fn[100] = "mecung2.txt";
	
	// JRB node;
	char *name2, *name1;
	int v2, v1;
	int total, n, *output, *outdoor;
	// Array1 *a;
	// char again='y';
	double distance;
	double mindistance = 100000000;
	int max = -1000000000;
	JRB node;
    // --------------------------------
    // parent = (int*)malloc(sizeof(int) * count_vertices(G));
	int choose = 0;
	do {
		choose = menu();
		switch (choose) {
			case 1:
			log(" Enter file name: ");
			while (getchar() != '\n');
			scanf("%[^\n]s", fn);
			
			if (G.vertices || G.edges)
				drop_graph(&G);
			G = create_graph();

			add_all_vertices(G, fn);
			add_all_edges(G, fn);

			log(" Import data success!\n");
			log(" Summary: \n");
			printf("	All work:\n");
			print_all_vertices(G);
			// print_graph(G);
			printf("	- Number of \"cong viec\": %d\n", count_vertices(G));
			printf("	- Number of \"so quan he\": %d\n", count_edges(G, UNDIRECTED));
			// endinput:
			// jettison_inputstruct(is);
			break;
			// 
			case 2:
			name2 = (char*) malloc(sizeof(char) * 10);
			log(" Enter family member: ");
			readLn(stdin, name2, 10);
			v2 = get_vertex_id(G, name2);
			printf("id: %d\n", get_vertex_id(G, name2));
			if (v2 <= 0) {
				printf("	- Dinh %s khong ton tai \n", name2);
			} else {
				output = (int*)malloc(sizeof(int) * count_vertices(G));
				total = out_degree(G, v2, output);
				printf(" - Dinh lien ke voi %s\n", name2);
				print_list_vertices(G, output, total);
			}
			break;
			// 
			case 3:
			name1 = (char*) malloc(sizeof(char) * 10);
			log(" Enter first vertex: ");
			readLn(stdin, name1, 10);
			v1 = get_vertex_id(G, name1);
			printf("id: %d\n", get_vertex_id(G, name1));

			name2 = (char*) malloc(sizeof(char) * 10);
			log(" Enter second vertex: ");
			readLn(stdin, name2, 10);
			v2 = get_vertex_id(G, name2);
			printf("id: %d\n", get_vertex_id(G, name2));
			if (v1 <= 0 || v2 <= 0) {
				printf("	- Dinh khong ton tai\n");
			} else {
				output = (int*)malloc(sizeof(int) * count_vertices(G));
				distance = shortest_path(G, v1, v2, output, &total);
				printf("Distance: %.f\n", distance);
				print_list_vertices(G, output, total);
			}
			break;
			// 
			case 4:
			outdoor = (int*)malloc(sizeof(int) * count_vertices(G));
			output = (int*)malloc(sizeof(int) * count_vertices(G));
			name1 = (char*) malloc(sizeof(char) * 10);
			log(" Enter first vertex: ");
			readLn(stdin, name1, 10);
			v1 = get_vertex_id(G, name1);
			printf("id: %d\n", get_vertex_id(G, name1));
			if (v1 <= 0) {
				printf("	- Dinh khong ton tai\n");
			} else {
				total = get_all_out_door(G, fn, outdoor);
				for (int i = 0; i < total; i++)	{
					distance = shortest_path(G, v1, outdoor[i], output, &n);
					if (distance < mindistance && outdoor[i] != v1) {
						mindistance = distance;
						v2 = outdoor[i];
					}
				}
				distance = shortest_path(G, v1, v2, output, &n);
				print_list_vertices(G, output, n);
			}
			free(outdoor);
			free(output);
			break;
			// 
			case 5:
			output = (int*)malloc(sizeof(int) * count_vertices(G));
			jrb_traverse(node, G.vertices) {
				v1 = jval_i(node->key);
				total = dfs2(G, v1, -1, output);
				if (total > max) {
					max = total;
					v2 = v1;
				}				
			}
			total = dfs2(G, v2, -1, output);
			print_list_vertices(G, output, total);
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