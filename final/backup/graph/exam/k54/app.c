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
	@ Nhap file tu ban phim
	--------------------------------
	*/
	// printf("[+] enter file name:");
	// scanf("%s", fn);



	/*
	@ main menu
	*/

	do{
		menu();
		m = scan_int("choose:");
		switch(m){
			case 1:
				/*
				@ Import to graph
				*/
				if(G.vertices || G.edges)
					drop_graph(&G);
				G = create_graph();
				add_all_vertices(G, fn);
				add_all_edges(G, fn);

				/*
				@ Thong ke ket qua
				*/
				print_graph_as_matrix(G);

				break;
			case 2:
				printf("[+] Summary:\n");
				printf("   - All vertices:\n");
				print_all_vertices(G);
				printf("   - Number of vertices:%d\n", count_vertices(G));
				printf("   - Number of edges:%d\n", count_edges(G, UNDIRECTED));
				// while(again!='n'){
				// 	printf("[+] Enter job name:");
				// 	scanf("%s", name);
				// 	getchar();
				// 	v = get_vertex_id(G, name);
				// 	if (v < 0){
				// 		printf("    error: could not find '%s'\n", name);
				// 		goto end;
				// 	}
				// 	else{
				// 		output = (int*)malloc(sizeof(int) * count_vertices(G));

				// 		total = get_adjacent_vertices_in_edge(G, v, output);
				// 		printf("[+] Info of job must be done first:\n");
				// 		printf("    - total number of job: %d\n", total);
				// 		printf("    - list of job:\n");
				// 		for(i=0; i<total; i++)
				// 			printf("        '%s'\n", get_vertex_val(G, output[i]));

				// 		get_topological_queue(G, output, &total);
				// 		n = count_prequisites(G, v);
				// 		printf("    Info of all jobs must be done before:\n");
				// 		printf("    - total number of job: %d\n", n);
				// 		printf("    - list of job:\n");
				// 		for(i=0; i<n; i++)
				// 			printf("        '%s'\n", get_vertex_val(G, output[i]));

				// 		free(output);
				// 	}
				// 	end:
				// 		again = scan_char("Do you wanna continue?[press 'n' to stop]");
				// }
				// again = 'y';
				break;
			case 3:
				printf("[+] Enter vertex name:");
				scanf("%[^\n]s", name);
				getchar();
				v = get_vertex_id(G, name);
				if (v < 0){
					printf("    error: could not find '%s'\n", name);
					break;
				}
				else{
					print_all_adjacent(G, v);
				}
				break;
			case 4:
				printf("[+] enter v1:");
				scanf("%[^\n]s", name1);
				getchar();
				printf("[+] enter v2:");
				scanf("%[^\n]s", name2);
				getchar();
				v1 = get_vertex_id(G, name1);
				v2 = get_vertex_id(G, name2);
				if(v1 < 0 || v2 < 0){
					puts("    - invalid input!\n");
					break;
				}
				printf("   - shortest path from '%s' to '%s':", name1, name2);
				print_shortest_path(G, v1, v2);
				printf("\n");
				break;
			case 5:
				printf("[+] Enter vertex name:");
				scanf("%[^\n]s", name);
				getchar();
				v = get_vertex_id(G, name);
				if (v < 0){
					printf("    error: could not find '%s'\n", name);
					break;
				}
				else if(!strstr(name, "0") && !strstr(name, "4")){
					printf("    error: not a cong vao\n");
					break;
				}
				else{
					n = count_vertices(G);
					output = (int*)malloc(sizeof(int)*n);
					m = get_related_vertices_sorted_by_path_length(G, v, output);
					if(!m){
						printf("    - there is no exit\n");
					}
					else{
						for(i=0; i<m; i++){
							strcpy(name, get_vertex_val(G, output[i]));
							if(strstr(name, "0") || strstr(name, "4")){
								printf("path:");
								print_shortest_path(G, v, get_vertex_id(G, name));
								break;
							}
						}
					}
					free(output);
				}	
				break;
			case 6:
				n = count_vertices(G);
				output = (int*)malloc(sizeof(int)*n);
				printf("[+] List of items in maximum connected part is:\n");
				m = get_maximum_connected_part(G, output);
				print_list_vertices(G, output, m);

				printf("[+] List of items in mimimum connected part is:\n");
				m = get_minimum_connected_part(G, output);
				print_list_vertices(G, output, m);

				free(output);
				break;
			case 7:
				puts("___Goodbye___");
				break;
			default:
				printf("error!\n");
		}
	}while(m!=7);

	return 0;
}
