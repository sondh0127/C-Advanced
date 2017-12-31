#ifndef HUFF_MAN_H
#define HUFF_MAN_H
#include "../../lib/include/jrb.h"
#include "graph_weighted_jrb.h"

typedef struct
{
	Graph_W graph;
	JRB root;
} Huffman_Tree;

typedef struct
{
	int size;
	char bits[2];
} Coding;

Huffman_Tree makeHuffman(char *buffer, int size);
#endif /* HUFF_MAN_H */
