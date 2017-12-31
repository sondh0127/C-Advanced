#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "graph_weighted_jrb.h"
#include "huffman.h"
#include "../../lib/include/dllist.h"

void show_int(int num)
{
	printf("%4d ", num);
}

int main(int argc, char const *argv[])
{
	char *s = "Eerie eyes seen near lake.";
    makeHuffman(s, strlen(s));
	return 0;
}