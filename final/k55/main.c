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
	char fn[100] = "topo.txt";
	
	// JRB node;
	char *name2;
	int v2;
	int total, n, *parent, *output;
	Array1 *a;
	char again='y';
	double time;
    // --------------------------------
	int choose = 0;
	do {
		choose = menu();
		switch (choose) {
			case 1:
			if (G.vertices || G.edges)
				drop_graph(&G);
			G = create_graph();

			add_all_vertices_and_edges(G, fn);
			log(" Import data success!\n");
			log(" Summary: \n");
			printf("	All work:\n");
			print_all_vertices(G);
			// print_graph(G);
			printf("	- Number of \"cong viec\": %d\n", count_vertices(G));
			printf("	- Number of \"so quan he\": %d\n", count_edges(G, DIRECTED));
			// endinput:
			// jettison_inputstruct(is);
			break;
			// 
			case 2:
			while (again != 'n') {

				name2 = (char*) malloc(sizeof(char) * 10);
				log(" Enter family member: ");
				readLn(stdin, name2, 10);
				v2 = get_vertex_id(G, name2);
				printf("id: %d\n", get_vertex_id(G, name2));


				if (v2 <= 0) {
					printf("	- Cong viec khong co trong chuong trinh\n");
					goto end;
				} else {
					parent = (int*)malloc(sizeof(int) * count_vertices(G));
					total = in_degree(G, v2, parent);
					if (total != 0) {
						printf("	- Number of job must be done before '%s': %d\n",name2, total);
						log(" List of job:\n");
						print_list_vertices(G, parent, total);
						printf("\n");
					// ancestor
						// a = (Array1*) malloc(sizeof(Array1));
						// a = All_node_visited(G,v2);
						// printf("	- All jobs must be done before '%s': %d\n",name2, a->num);
						// for (int i = a->num - 1; i >= 0; i--) {
						// 	printf("	- %s\n",get_vertex_name(G,a->A[i]));
						// }
						// printf("\n");
						output = (int*)malloc(sizeof(int) * count_vertices(G));
						total = get_all_ancestor(G, v2, output);
						printf("	- All jobs must be done before '%s': %d\n",name2, total);
						print_list_vertices(G, output, total);
						
						// n = count_vertices(G);
						// output = (int*)malloc(sizeof(int) * n);
						// topologicalSort_no_counti(G, output, &total);
						// printf("v2: %d\n", v2);
						// if (total != 0) {
						// 	for (int i = 0; i < total; i++) {

						// 		if (output[i] == v2) {
						// 			n = i;
						// 			break;		
						// 		}
						// 		printf("	- %d \n", output[i]);
						// 	}
						// }
						// printf("	- All jobs must be done before '%s': %d\n",name2, n);
						
						printf("\n");

					} else {
						printf("	- Khong co cong viec phai lam truoc '%s':\n", name2);
					}
				}

				end:
				printf("	- Do you wanna continue ? [press 'n' to stop]: ");
				// while (getchar() != '\n');
				scanf("%c",&again);
				again = tolower(again);
			}
			again = 'y';
			break;
			// 
			case 3:
			if (is_cycle(G)) {
				printf("	- Khong co thu tu sap xep cong viec!\n");
			} else {
				printf("	- Thu tu sap xep cong viec theo trinh tu truoc sau la: \n");
				n = count_vertices(G);
				output = (int*)malloc(sizeof(int) * n);
				topologicalSort_no_counti(G, output, &total);
				if (total != 0) {
					print_list_vertices(G, output, total);
				}
			}
			free(output);
			break;
			// 
			case 4:
			name2 = (char*) malloc(sizeof(char) * 10);
			log(" Enter family member: ");
			readLn(stdin, name2, 10);
			v2 = get_vertex_id(G, name2);
			printf("id: %d\n", get_vertex_id(G, name2));

			if (v2 <= 0) {
				printf("	- Cong viec khong co trong chuong trinh\n");
			} else {
				output = (int*)malloc(sizeof(int) * count_vertices(G));
				time = get_shortest_time(G, v2, output, &total);
				printf("	- Shortest time: %.f (day(s))\n", time);
				print_list_vertices(G, output, total);
			}
			break;
			// 
			case 5:
			log(" Checking cyclic property: \n");
			// printf("weight 3->1=%.f\n", get_edge_weight(G, 3, 1));
			if(is_cycle(G)){
				printf("	- invalid (graph is cyclic)!\n");
			} else {
				printf("	- ok (graph is not cyclic) !\n");
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