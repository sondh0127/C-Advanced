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
	IS is;
	Graph G;
	char fn[100] = "giapha1.txt";
	int m,n;
	int v1, v2, mode;
	char *name;
	int *output, length;
	int flag, v, c1, c2, c3;
	JRB node;
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

			is = new_inputstruct(fn);
			if (!is) {
				printf("	- input error, no such file or directory!\n");
				break;
			}
			get_line(is);
			n = atoi(is->fields[0]);
			m = atoi(is->fields[1]);
			// printf("%d %d\n", n, m);

			for (int i = 0; i < n; i++) {
				get_line(is);
				name = (char *)malloc(sizeof(char)*10);
				strcpy(name, is->fields[0]);
				add_vertex_auto_increment(G, name);
				// printf("%s\n", name);
			}

			for (int i = 0; i < m; i++) {
				get_line(is);
				v1 = atoi(is->fields[0]);
				v2 = atoi(is->fields[1]);
				mode = atoi(is->fields[2]);
				// printf("%d %d %d\n", v1, v2, mode);
				if (mode == 0)
					add_edge(G, v1, v2, DAD, DIRECTED);
				else if (mode == 1)
					add_edge(G, v1, v2, MOM, DIRECTED);
				else {
					printf("	- invalid input (relation value = %d)\n", mode);
					goto endinput;
				}
			}

			log(" Import data success!\n");
			log(" Summary: \n");
			printf("	All members:\n");
			print_all_vertices(G);
			printf("	- Number of members: %d\n", count_vertices(G));
			printf("	- Number of relations: %d\n", count_edges(G, DIRECTED));
			endinput:
			// free(name);
			jettison_inputstruct(is);
			break;
			// 
			case 2:

			flag = true;
			jrb_traverse(node, G.vertices) {
				v = jval_i(node->key);
				c1 = is_mom_or_dad_only(G, v);
				printf("	+ checking '%s'- result = %d\n", get_vertex_name(G, v), c1);
				if(!c1)
					flag = false;
			}
			if(flag)
				log(" Summary: CONSISTENT\n");
			else
				log(" Summary: INCONSISTENT\n");
			break;
			// 
			case 3:

			flag = true;
			jrb_traverse(node, G.vertices) {
				v = jval_i(node->key);
				c2 = no_more_than_one_mom_or_dad(G, v);
				printf("	+ checking 2 '%s'- result = %d\n", get_vertex_name(G, v), c2);
				if(!c2)
					flag = false;
			}
			if (flag)
				log(" Summary: CONSISTENT\n");
			else
				log(" Summary: INCONSISTENT\n");
			break;
			// 
			case 4:
			flag = true;
			c3 = is_cycle(G);
			if(c3)
				flag = false;
			printf("	+ checking is cyclic graph: %d\n", c3);
			if(flag)
				log(" Summary: CONSISTENT\n");
			else
				log(" Summary: INCONSISTENT\n");		
			break;
			// 
			case 5:
			// need check 3 flag before ?
			name = (char*)malloc(sizeof(char) * 100);
			log(" Enter family member: ");
			readLn(stdin, name, 100);
			v2 = get_vertex_id(G, name);
			if (v2 <= 0)
				printf("	- Family do not have that member\n");
			else {
				output = (int*)malloc(sizeof(int)*count_vertices(G));
				length = get_sibling(G, v2, output);
				if( length == 0){
					printf("	- He/she has no sibling!\n");
				} else {
					printf("	- List of sibling of '%s':\n", get_vertex_name(G, v2));
					print_list_vertices(G, output, length);
				}
				free(output);
			}
			free(name);
			break;
			// 
			case 6:
			name = (char*)malloc(sizeof(char) * 100);
			log(" Enter family member: ");
			readLn(stdin, name, 100);
			v = get_vertex_id(G, name);
			if (v <= 0)
				printf("	- Family do not have that member\n");
			else {
				output = (int*)malloc(sizeof(int)*count_vertices(G));
				length = get_all_grand_children(G, v, output);
				if(length==0){
					printf("	- He/she has no grandchild\n");
				}
				else {
					printf("	- List of grand children:\n");
					print_list_vertices(G, output, length);
				}
				free(output);
			}
			free(name);
			break;
			// 
			case 7:
			name = (char*)malloc(sizeof(char) * 100);
			log(" Enter family member: ");
			readLn(stdin, name, 100);
			v = get_vertex_id(G, name);
			if (v <= 0)
				printf("	- Family do not have that member\n");
			else {
				printf("	- List of descendant:\n");
				print_all_descendants(G, v);
			}
			free(name);
			break;
			// 
			case 8:
			if (G.vertices || G.edges)
				drop_graph(&G);
			printf("	- Exited!\n");
			break;
			// 
			default:
			printf("	- Invalid input! Type (1-8)\n");
			break;  
		}
	}  while (choose != 8);
	return 0;
}