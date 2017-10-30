#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "extio.h"
#include "main.h"
#include "../../lib/include/jrb.h"
#include "../../lib/include/btree.h"
#include "graph_jrb.h"

#define MAXSECTION 5

/* FUNCTION DEF */
int menu() {
	int choose = 0;
	int MAX = 5;
	char menu[][40] = { "Input from file", 
						"Search for friends", 
						"Print out", 
						"Show people have common friends", 
						"Save and exit"};

	printf("\n\t================================\n");
	printf(  "\t============| MENU |============\n");
	printf(  "\t================================\n");
	for(int i = 0; i < MAX; i++)
		printf("\t%d. %s\n", i+1, menu[i]);
	printf("Enter your chose: ");
	while(scanf("%d", &choose) != 1) {
		printf("Input must be integer!\n");
		while (getchar() != '\n' );
		//wasting the buffer till the next new line
		printf("Enter your choose: ");
	}
	return choose;	
}

int main(int argc, char *argv[])
{
	if(argc != 2) {
		printf("Usage: main filename\n");
		exit(1);
	}
	char *filename = strdup(argv[1]);
	map input;
	char search[100];

	int choose;
	do {
		choose = menu();
		switch (choose) {
		case 1:
			input = inputfromFile(filename);
			showVertices(input);
			printf("\n");
			break;
		case 2:
			printf("Type in a name: ");
			readLn(stdin, search, 100);
			showAdjacent(input, search);
			break;
		case 3:
			printf("Report: \n");
			printOut(input);
			break;
		case 4:
			printf("Type in a name: ");
			readLn(stdin, search, 100);
			hasCommonFriends(search, input);
			break;
		case MAXSECTION:
			free(input.list);
			dropGraph(input.graph);
			break;
		default:
			printf("Choice must be from 1 to %d\n", MAXSECTION);
			exit(1);
		}
	} while (choose != MAXSECTION && choose != 0);
}

int checkName(char p1[], map data)
{
	int i = 0;
	for (i = 0; i < data.number; ++i)
		if (strcmp(p1, data.list[i].name) == 0)
			return i;
	return -1;
	//0 means diff
}

map inputfromFile(char *filename)
{
	int v1, v2;
	map data;
	char p1[100], p2[100];
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Can't Open file %s !!\n", filename);
		exit(1);
	}

	fscanf(f, "%d\n", &data.relationship_num);
	// printf("data number: %d\n", data.relationship_num);
	data.list = (person *)malloc(sizeof(person) * data.relationship_num * 2);
	data.graph = createGraph();
	data.number = 0;

	for (int i = 0; i < data.relationship_num; ++i)	{
		fscanf(f, "\"%[^\"]\" \"%[^\"]\"\n", p1, p2);
		// printf("%s %s\n", p1, p2);
		if (checkName(p1, data) == -1)
			strcpy(data.list[data.number++].name, p1);

		v1 = checkName(p1, data);
		if (checkName(p2, data) == -1)
			strcpy(data.list[data.number++].name, p2);
		v2 = checkName(p2, data);
		// printf("%d %d\n", v1, v2);
		addEdge(data.graph, v1, v2);
	}

	for (int i = 0; i < data.number; ++i)
		data.list[i].friends_num = 0;
	printf("Input success!\n");
	return data;
	fclose(f);
}

void showVertices(map data)
{
	printf("Total vertices: %d\n", data.number);
	printf("Total edges: %d\n", data.relationship_num);
}

void showNode(map input, int vertex)
{
	printf(" %s ", input.list[vertex].name);
}

void showAdjacent(map input, char name[])
{
	int i;
	int v1 = -1;
	int output[10];
	int numberofAdjacent;
	v1 = checkName(name, input)
	// for(i = 0; i < input.number; ++i)
	// 	if (strcmp(input.list[i].name, name) == 0)
	// 	{
	// 		v1 = i;
	// 		break;
	// 	}
	if (v1 != -1) {
		numberofAdjacent = getAdjacentVertices(input.graph, v1, output);
		// printf("%d\n", numberofAdjacent);
		printf("Friends of %s are: ", name);
		for (i = 0; i < numberofAdjacent; ++i)
			showNode(input, output[i]);
		printf("\n\n");
	} else
		printf("Wrong name\n");
}

void printOut(map data)
{
	int max = 0;
	int temp[data.number];
	int numberfriends[data.number];
	for (int i = 0; i < data.number; ++i)
	{
		data.list[i].friends_num = getAdjacentVertices(data.graph, i, temp);
		numberfriends[i] = data.list[i].friends_num;
		if (max < numberfriends[i])
			max = numberfriends[i];
	}


	for (int j = 1; j <= max; ++j)
	{
		printf("%d ", j);
		for (int i = 0; i < data.number; ++i)
			if (data.list[i].friends_num == j)
				printf(" \"%s\" ", data.list[i].name);
		printf("\n");
	}
}

void hasCommonFriends(char name[], map data)
{
	int numberofAdjacent;
	int v1;
	int v2;
	int i;
	int flag = 0;
	int visited[data.number];
	int output[data.number];

	for (i = 0; i < data.number; ++i)
		visited[i] = 0;
	v1 = checkName(name, data);
	// for (i = 0; i < data.number; ++i)
	// 	if (strcmp(data.list[i].name, name) == 0)
	// 	{
	// 		v1 = i;
	// 		break;
	// 	}
	if (v1 != -1)
	{
		numberofAdjacent = getAdjacentVertices(data.graph, v1, output);
		// printf("%d\n", numberofAdjacent);
		printf("People have common friends with %s are: ", name);
		for (i = 0; i < numberofAdjacent; ++i)	{
			v2 = output[i];
			for (int j = 0; j < data.number; ++j)
			{
				if (isAdjacent(data.graph, v2, j))
				{
					if (j != v1 && visited[j] != 1)
					{
						showNode(data, j);
						visited[j] = 1;
					}
					flag = 1;
				}
			}
		}
		if (flag == 0)
			printf("No common friends\n");
		printf("\n\n");
	}
	else
		printf("Wrong name\n");
}