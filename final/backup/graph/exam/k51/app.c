// #define log(...) printf("")
#include "graph/graph.h"
#include "libfdr/fields.h"
#include <stdio.h>
#include <stdlib.h>
Graph G;
#include "api.h"

int main(){
	/*
	@ import raw data
	*/
	IS is;
	int i, matrix[5][5];
	is = new_inputstruct("testcase.txt");
	while(get_line(is) >= 0)
		for(i=0; i < is->NF; i++){
			log("matrix[%d][%d]=\"%s\"\n", is->line, i, is->fields[i]);
			matrix[is->line-1][i] = atoi(is->fields[i]);
		}

	/*
	@ add raw data to graph
	*/
	G = create_graph();
	add_all_vertex(G, matrix);
	add_all_edge(G, matrix);
	
	/*
	@ main menu
	*/
	int m;
	int id, *output;
	char s[100];
	char s1[100], s2[100];
	int v1, v2;
	do{
		menu();
		printf("choose:");
		scanf("%d", &m);
		switch(m){
			case 1:
				print_all_vertex(G);
				break;
			case 2:
				printf("total vertices: %d\n", count_vertices(G));
				printf("total edge    : %d\n", count_edges(G, UNDIRECTED));
				break;			
			case 3:
				printf("enter vertex name:");
				scanf("%s", s);
				id = get_vertex_id(G, s);
				if(id < 0)
					printf("    [!] vertex '%s' not existed!\n", s);
				else
					print_all_adjacent(G, id);
				break;
			case 4:
				printf("List of node with more flux:\n");
				output = (int*)malloc(sizeof(int ) * count_vertices(G));
				get_vertices_id(G, output);
				qsort(output, count_vertices(G), sizeof(int), _increase_cmp);
				for(i=0; i < count_vertices(G); i++)
					printf("   - %d %s\n", count_adjacent(G, output[i]), get_vertex_val(G, output[i]));
				free(output);
				break;
			case 5:
				printf("List of node with no flux:\n");
				output = (int*)malloc(sizeof(int ) * count_vertices(G));
				get_vertices_id(G, output);
				for(i=0; i < count_vertices(G); i++)
					if(count_adjacent(G, output[i])==0)
						printf("    - %d %s\n", count_adjacent(G, output[i]), get_vertex_val(G, output[i]));
				free(output);
				break;
			case 6:
				printf("start point:");
				scanf("%s", s1);
				printf("end point:");
				scanf("%s", s2);
				v1 = get_vertex_id(G, s1);
				v2 = get_vertex_id(G, s2);			
				print_shortest_path(G, v1, v2);
				break;
			case 8:
				break;
			default:
				printf("error!\n");
		}
	}while(m!=8);	

	jettison_inputstruct(is);
	return 0;
}