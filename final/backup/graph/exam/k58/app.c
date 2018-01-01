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
	char *name1, *name2, *name;
	name1 = (char*)malloc(sizeof(char)*10);
	name2 = (char*)malloc(sizeof(char)*10);
	int v1, v2;
	int m;
	int id, *output;
	G = create_graph();
	char ctn;
	int length;
	/*
	@ main menu
	*/

	do{
		menu();
		printf("choose:");
		scanf("%d", &m);
		switch(m){
			case 1:
				/*
				@ Nhap file tu ban phim
				--------------------------------
				printf("[+] enter file name:");
				scanf("%s", fn);
				*/

				is = new_inputstruct(fn);
				if(!is){
					printf("error");
					return 1;
				}

				if(get_line(is) >= 0){
					// log("line=%s\n", is->fields[0]);
					n = atoi(is->fields[0]);
				}

				if(G.vertices || G.edges)
					drop_graph(&G);
				G = create_graph();

				for(j=0; j<n; j++){
					get_line(is);

					// add all vertices
					for(i=0; i < is->NF; i++){
						// log("data[%d][%d]='%s'\n", is->line, i, is->fields[i]);
						name = (char*)malloc(sizeof(char)*10);
						strcpy(name, is->fields[i]);
						add_vertex_auto_increment(G, name);
						log("add vertex: %s\n", name);
					}
					// add all edges
					for(i=1; i < is->NF; i++){
						strcpy(name2, is->fields[0]);
						strcpy(name1, is->fields[i]);
						add_edge(G, get_vertex_id(G, name1), get_vertex_id(G, name2),1, DIRECTED);
						log("add edge: '%s'->'%s'\n", name1, name2, count_edges(G, DIRECTED));
					}
				}
				log("import data success!\n");
				printf("[+] Summary:\n");
				printf("   - All vertices:\n");
				print_all_vertices(G);
				printf("   - Number of subject:%d\n", count_vertices(G));
				printf("   - Number of relation:%d\n", count_edges(G, DIRECTED));
				break;
			case 2:
				printf("[+] Checking cyclic property:");
				if(is_cyclic(G))
					printf(" invalid (graph is cyclic)\n");
				else
					printf(" ok (graph is not cyclic)\n");
				break;			
			case 3:
				ctn = 'y';
				while(ctn!='n'){
					// Input name of subject
					name = (char*)malloc(sizeof(char) * 10);
					printf("[+] Enter subject:");
					scanf("%s", name);
					id = get_vertex_id(G, name);
					if (id < 0){
						printf("    - Subject does not exist\n");
						free(name);
						break;
					}
					else{
						free(name);
						// Perform topological sort
						// Print all subject before choosen subject
						printf("      - Prerequisite of subject:");
						output = (int*)malloc(sizeof(int)*count_vertices(G));
						get_topological_queue(G, output, &length);

						for(i=0; i < length; i++){
							printf("%s->", get_vertex_val(G, output[i]));
							if(output[i] == id)
								break;
						}
						putchar('\n');
						free(output);								
					}
					printf("do you wanna continue[Y/n]?");
					getchar();
					scanf("%c", &ctn);
				}
				break;
			case 4:
				print_all_path(G, get_vertex_id(G, "0"), get_vertex_id(G, "4"));
				break;
			case 5:
				printf("[+] List of subjects sort by number of prerequisites ascending:\n");
				output = (int*)malloc(sizeof(int ) * count_vertices(G));
				get_vertices_id(G, output);
				qsort(output, count_vertices(G), sizeof(int), _asc_cmp);
				for(i=0; i < count_vertices(G); i++)
					printf("   - Subject: %s, number of prerequisites %d\n", 
						get_vertex_val(G, output[i]), count_prerequisites(G, output[i]));
				free(output);
				break;
			case 6:
				printf("[+] List of subjects order sort by topo:\n");
				topological_sort(G, menu6);
				break;
			case 7:
				printf("[+] Exiting\n");
				break;
			default:
				printf("error!\n");
		}
	}while(m!=7);

	jettison_inputstruct(is);
	return 0;
}