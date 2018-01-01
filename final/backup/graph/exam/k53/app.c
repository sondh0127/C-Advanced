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
	int max_length;
	/*
	@ Nhap file tu ban phim
	--------------------------------
	*/
	// printf("[+] enter file name:");
	// scanf("%s", fn);

	/*
	@ Import to graph
	*/
	if(G.vertices || G.edges)
		drop_graph(&G);
	G = create_graph();
	add_all_vertices(G, fn);
	add_all_edges(G, fn);


	/*
	@ main menu
	*/

	do{
		menu();
		m = scan_int("choose:");
		switch(m){
			case 1:

				/*
				@ Thong ke ket qua
				*/
				printf("[+] Summary:\n");
				printf("   - List of people:\n");
				print_all_vertices(G);
				printf("   - Number of people:%d\n", count_vertices(G));
				break;
			case 2:
				printf("[+] Graph summary:\n");
				printf("   - Number of nodes:%d\n", count_vertices(G));
				printf("   - Number of relations:%d\n", count_edges(G, UNDIRECTED));
				break;
			case 3:
				n = count_vertices(G);
				output = (int*)malloc(sizeof(int)*n);
				get_vertices_sorted_by_adjacent(G, output);
				for(i=0; i<n; i++)
					print_all_adjacent(G, output[i]);
				free(output);
				break;
			case 4:
				while(again != 'q'){
					printf("[+] Enter a people:");
					scanf("%[^\n]s", name);
					getchar();
					v = get_vertex_id(G, name);
					if (v < 0){
						puts("    - invalid input !");
						goto end;
					}
					n = count_vertices(G);
					output = (int*)malloc(sizeof(int) * n);
					m = get_related_vertices_sorted_by_path_length(G, v, output);
					printf("[+] List %d mutual friends of '%s':\n", m, name);
					if (m > 0){
						max_length = shortest_path_length(G, v, output[m-1]);
						for(i=1; i<=max_length ; i++){
							printf("     ban cap %d:", i);
							for(j=0; j<m; j++)
								if(i==shortest_path_length(G, v, output[j]))
									printf(" '%s' ", get_vertex_val(G, output[j]));
							printf("\n");
						}
					}
					end:
					free(output);
					again = scan_char("do you want to quit [press 'q' to quit]\n");
				}
				again = 'y';
				break;	
			case 5:
				break;
			default:
				printf("error!\n");
		}
	}while(m!=5);

	return 0;
}
