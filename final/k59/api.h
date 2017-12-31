#ifndef API_H
#define API_H 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define DAD 1
#define MOM 2

// API
int menu() {
	int choose = 0;
	int MAX = 8;
	char menu[][100] = { "Import data to graph", 
	"Check consistentcy, a member cannot not be both mom and dad", 
	"Check consistentcy, a member cannot has more than one mom or dad", 
	"Check consistentcy, check circle in graph" ,
	"Print all sibling",
	"Print all grandchildren",
	"Print all descendances",
	"Exit"};

	printf("\n\t\t================================\n");
	printf(  "\t\t============| MENU |============\n");
	printf(  "\t\t================================\n");
	for(int i = 0; i < MAX; i++)
		printf("\t%d) %s\n", i+1, menu[i]);
	printf("[+] Enter your chose: ");
	while(scanf("%d", &choose) != 1) {
		printf("	- Input must be integer!\n");
		while (getchar() != '\n' );
        //wasting the buffer till the next new line
		printf("[+] Enter your choose: ");
	}
	return choose;  
}

int is_mom_or_dad_only(Graph G, int v) {
	int n = count_vertices(G);
	int output[n];
	int m = out_degree(G, v, output);
	int v2;
	double w;
	int flag = UNDEFINED;
	//set for root element
	v2 = output[0];
	flag = get_edge_weight(G, v, v2);

	for(int i = 0; i < m; i++){
		v2 = output[i];
		w = get_edge_weight(G, v, v2);
		if(flag != w){
			return false;
		}
	}
	return true;
}

int no_more_than_one_mom_or_dad(Graph G, int v2){
	int n = count_vertices(G);
	int output[n];
	int count = in_degree(G, v2, output);
	int v;
	double w;
	int count_mom = 0, count_dad = 0;
	for(int i = 0; i < count; i++) {
		v = output[i];
		w = get_edge_weight(G, v, v2);
		if (w == MOM)
			count_mom++;
		if (w == DAD)
			count_dad++;
	}
	if (count_mom <=1 && count_dad <=1)
		return true;
	else
		return false;
}

int in_array(int v, int *array, int n){
	int i;
	for(i=0; i<n; i++){
		if(array[i] == v)
			return true;
	}
	return false;
}

void print_list_vertices(Graph G, int *output, int n){//ok
	int i;
	for( i = 0; i < n; i++)
		printf("	- %s\n", get_vertex_name(G, output[i]));
}

int get_sibling(Graph G, int v2, int *output){
	int mom, dad, v;
	double w;
	int n = count_vertices(G);
	int parent[n];
	int count = in_degree(G, v2, parent);
	for (int i = 0; i < count; i++){
		v = parent[i];
		w = get_edge_weight(G, v, v2);
		if(w == MOM)
			mom = v;
		if(w == DAD)
			dad = v;
	}

	for(int i = 0; i < n; i++)
		output[i] = 0;
	int total = 0;
	int temp[n];

	count = out_degree(G, mom, temp);
	for(int i = 0; i < count; i++) {
		v = temp[i];
		if(!in_array(v , output, n) && v != v2)
			output[total++] = v;
	}
	count = out_degree(G, dad, temp);
	for(int i = 0; i < count; i++) {
		v = temp[i];
		if(!in_array(v , output, n) && v != v2)
			output[total++] = v;
	}
	return total;
}

int get_all_grand_children(Graph G, int v, int *output){
	int *children, *grandchildren, n, n_children, n_grandchildren, i, j, v2, v_child;
	n = count_vertices(G);
	children = (int*)malloc(sizeof(int) * n);
	grandchildren = (int*)malloc(sizeof(int) * n);
	n_children = out_degree(G, v, children);

	for(i=0; i<n; i++)
		output[i] = 0;

	int total = 0;
	// printf("  -List of child:\n");
	// print_list_vertices(G, children, n_children);

	for(i=0; i<n_children; i++){
		v_child = children[i];
		n_grandchildren = out_degree(G, v_child, grandchildren);
		for(j=0; j<n_grandchildren; j++){
			v2 = grandchildren[j];
			if(!in_array(v2 , output, n))
				output[total++] = v2;
		}

		// printf("  -List of child of '%s':\n", get_vertex_name(G, v_child));
		// print_list_vertices(G, grandchildren, n_grandchildren);
	}
	free(children);
	free(grandchildren);
	return total;
}

int _self;
void _print_a_descendant(Graph G, int v) {
	if(v != _self)
		printf("	- '%s'\n", get_vertex_name(G, v));
}

void print_all_descendants(Graph G, int v) {
	_self = v;
	bfs(G, v, -1, _print_a_descendant);
}




#endif