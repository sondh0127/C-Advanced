#include <stdio.h>
#include "sort.h"
#include <stdlib.h>
#include <string.h>

int comparator(const void* p, const void *q) {
	char *a = ((Phone*)p)->name;
	char *b = ((Phone*)q)->name;

	return (strcmp(a,b));	
}

