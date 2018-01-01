#include "graph/graph.h"
#include "libfdr/fields.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Graph G;
#define DAD 1
#define MOM 2
#include "api.h"

int main(){
	/*
	@ import raw data
	@ also add raw data to graph
	--------------------------------
	*/
	IS is;
	char fn[100] = "giapha1.txt";
	int n, m, i, j, k, mode;
	char *name1, *name2, *name;
	name1 = (char*)malloc(sizeof(char)*10);
	name2 = (char*)malloc(sizeof(char)*10);
	int v1, v2, v;
	int _m;
	int id, *output;
	G = create_graph();
	char ctn;
	int length;
	int c1, c2, c3, flag;
	/*
	@ main menu
	*/

	do{
		menu();
		_m = scan_int("choose:");
		switch(_m){
			case 1:
				
				// @ Nhap file tu ban phim
				// --------------------------------
				printf("[+] enter file name:");
				scanf("%[^\n]s", fn);
				getchar();

				if(G.vertices || G.edges)
					drop_graph(&G);
				G = create_graph();

				is = new_inputstruct(fn);
				if(!is){
					printf("    - input error, no such file or directory!\n");
					break;
				}
				get_line(is);
				n = atoi(is->fields[0]);
				m = atoi(is->fields[1]);

				for(i=0; i<n; i++){
					get_line(is);
					name = (char*)malloc(sizeof(char)*10);
					strcpy(name, is->fields[0]);
					add_vertex_auto_increment(G, name);
				}

				for(i=0; i<m; i++){
					get_line(is);
					v1 = atoi(is->fields[0]);
					v2 = atoi(is->fields[1]);
					mode = atoi(is->fields[2]);
					if(mode == 0)
						add_edge(G, v1, v2, DAD, DIRECTED);
					else if(mode == 1)
						add_edge(G, v1, v2, MOM, DIRECTED);
					else{	
						printf("    - invalid input (relation value = %d)\n", mode);
						goto endinput;
					}
				}

				log("import data success!\n");
				printf("[+] Summary:\n");
				printf("   - All members:\n");
				print_all_vertices(G);
				printf("   - Number of members:%d\n", count_vertices(G));
				printf("   - Number of relations:%d\n", count_edges(G, DIRECTED));
				endinput:
				jettison_inputstruct(is);
				break;
			case 2:
				output = (int*)malloc(sizeof(int)*n);
				m = get_vertices_id(G, output);
				flag = true;
				for(i=0; i<m; i++){
					v = output[i];
					c1 = is_mom_or_dad_only(G, v);
					printf("    + checking '%s': result=%d\n", get_vertex_val(G, v), c1);
					if(!c1)
						flag = false;
				}
				if(flag)
					printf("[+] Summary: CONSISTENT\n");
				else
					printf("[+] Summary: INCONSISTENT\n");
				free(output);
				break;			
			case 3:
				output = (int*)malloc(sizeof(int)*n);
				m = get_vertices_id(G, output);
				flag = true;
				for(i=0; i<m; i++){
					v = output[i];
					c2 = no_more_than_one_mom_or_dad(G, v);
					printf("    + checking '%s' result=%d\n", get_vertex_val(G, v), c2);
					if(!c2)
						flag = false;
				}
				if(flag)
					printf("[+] Summary: CONSISTENT\n");
				else
					printf("[+] Summary: INCONSISTENT\n");
				free(output);
				break;			
			case 4:
				flag = true;
				c3 = is_cyclic(G);
				if(c3)
					flag = false;
				printf("   - checking is cyclic graph:%d\n", c3);
				if(flag)
					printf("[+] Summary: CONSISTENT\n");
				else
					printf("[+] Summary: INCONSISTENT\n");
				break;			
			case 5:
				name = (char*)malloc(sizeof(char) * 100);
				printf("[+] enter family member:");
				scanf("%[^\n]s", name);
				getchar();
				v2 = get_vertex_id(G, name);
				if (v2 <= 0)
					printf("    - Family do not have that member\n");
				else{
					printf("  -List of sibling '%s':\n", get_vertex_val(G, v2));
					output = (int*)malloc(sizeof(int)*count_vertices(G));
					length = get_sibling(G, v2, output);
					if(length==0){
						puts("    - He/she has no sibling");
					}
					else{
						print_list_vertices(G, output, length);
					}
					free(output);
				}
				free(name);
				break;
			case 6:
				name = (char*)malloc(sizeof(char) * 100);
				printf("[+] enter family member:");
				scanf("%[^\n]s", name);
				getchar();
				v = get_vertex_id(G, name);
				if (v <= 0)
					printf("    - Family do not have that member\n");
				else{
					printf("  -List of grand children:\n");
					output = (int*)malloc(sizeof(int)*count_vertices(G));
					length = get_all_grand_children(G, v, output);
					if(length==0){
						puts("    - He/she has no grandchild");
					}
					else{
						print_list_vertices(G, output, length);
					}
					free(output);
				}
				free(name);
				break;
			case 7:
				name = (char*)malloc(sizeof(char) * 100);
				printf("[+] enter family member:");
				scanf("%[^\n]s", name);
				getchar();
				v = get_vertex_id(G, name);
				if (v <= 0)
					printf("    - Family do not have that member\n");
				else{
					printf("  -List of descendant:\n");
					print_all_descendants(G, v);
				}
				free(name);
				break;
			case 8:
				puts("Goodbye\n");
				break;
			default:
				printf("error!\n");
		}
	}while(_m!=8);

	return 0;
}