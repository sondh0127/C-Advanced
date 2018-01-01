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
	char fn[100] = "monhoc.txt";
	
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
			log(" Enter file name: ");
			while (getchar() != '\n');
			scanf("%[^\n]s", fn);
			
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
			name2 = (char*) malloc(sizeof(char) * 10);
				log(" Enter family member: ");
				readLn(stdin, name2, 10);
				v2 = get_vertex_id(G, name2);
				printf("id: %d\n", get_vertex_id(G, name2));
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
				
						output = (int*)malloc(sizeof(int) * count_vertices(G));
						total = get_all_ancestor(G, v2, output);
						printf("	- All jobs must be done before '%s': %d\n",name2, total);
						print_list_vertices(G, output, total);
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
			
			break;
			// 
			case 4:
			
			break;
			// 
			case 5:
			
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