#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "../../lib/include/jrb.h"
#include "../../lib/include/btree.h"
#include "graph_jrb.h"

typedef struct {
	char name[100];
	int friends_num;
} person;

typedef struct {
	Graph graph;
	person *list;
	int number;
	int relationship_num;
} map;
/* MAIN'S PROTOTYPE*/
int menu();
int checkName(char p1[], map data);
map inputfromFile(char *filename);
void showVertices(map data);
void showNode(map input, int vertex);

void showAdjacent(map input, char name[]);
void printOut(map data);
void hasCommonFriends(char name[], map data);
#endif /* MAIN_H */
