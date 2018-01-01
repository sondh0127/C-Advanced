#include "graph/graph.h"
#include "libfdr/fields.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Graph G;
#include "api.h"

int main(){
	/*
	@ import raw data
	@ also add raw data to graph
	--------------------------------
	*/
	IS is;
	char fn[100] = "testcase.txt";
	int n, i, j, k;
	int v1, v2;
	int m;
	int v, *output, total;
	char name[100], name1[100], name2[100];
	G = create_graph();
	char again='y';
	double *length, w;
	/*
	@ main menu
	*/

	do{
		menu();
		m = scan_int("choose:");
		switch(m){
			case 1:
				/*
				@ Nhap file tu ban phim
				--------------------------------
				*/
				// printf("[+] enter file name:");
				// scanf("%s", fn);

				if(G.vertices || G.edges)
					drop_graph(&G);
				G = create_graph();
				add_all_vertices(G, fn);
				add_all_edges(G,fn);
				printf("[+] Summary:\n");
				printf("   - All vertices:\n");
				print_all_vertices(G);
				printf("   - Number of subject:%d\n", count_vertices(G));
				printf("   - Number of relation:%d\n", count_edges(G, DIRECTED));
				break;
			case 2:
				while(again!='n'){
					printf("[+] Enter job name:");
					scanf("%s", name);
					getchar();
					v = get_vertex_id(G, name);
					if (v < 0){
						printf("    error: could not find '%s'\n", name);
						goto end;
					}
					else{
						output = (int*)malloc(sizeof(int) * count_vertices(G));

						total = get_adjacent_vertices_in_edge(G, v, output);
						printf("[+] Info of job must be done first:\n");
						printf("    - total number of job: %d\n", total);
						printf("    - list of job:\n");
						for(i=0; i<total; i++)
							printf("        '%s'\n", get_vertex_val(G, output[i]));

						get_topological_queue(G, output, &total);
						n = count_prequisites(G, v);
						printf("    Info of all jobs must be done before:\n");
						printf("    - total number of job: %d\n", n);
						printf("    - list of job:\n");
						for(i=0; i<n; i++)
							printf("        '%s'\n", get_vertex_val(G, output[i]));

						free(output);
					}
					end:
						again = scan_char("Do you wanna continue?[press 'n' to stop]");
				}
				again = 'y';
				break;
			case 3:
				printf("[+] List of job sorted by topo:\n");
				output = (int*)malloc(sizeof(int) * count_vertices(G));
				get_topological_queue(G, output, &total);
				for(i=0; i<total; i++)
					printf("        '%s'\n", get_vertex_val(G, output[i]));
				break;
			case 4:
				printf("[+] Enter job name:");
				scanf("%s", name);
				v = get_vertex_id(G, name);
				if (v < 0){
					printf("    error: could not find '%s'\n", name);
					break;
				}
				else
					printf("    Job must be done in %f hour(s)\n", topological_get_minimun_cost(G, v));
				break;
			case 5:
				printf("[+] Checking cyclic property:");
				if (is_cyclic(G))
					printf(" invalid (graph is cyclic)\n");
				else
					printf(" ok (graph is not cyclic)\n");
				break;
			case 6:
				break;
			case 7:
				printf("weight 1->1=%f\n", get_edge_weight(G, 1, 1));
				break;
			default:
				printf("error!\n");
		}
	}while(m!=6);

	return 0;
}
