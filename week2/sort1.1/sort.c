#include <stdio.h>
#include "sort.h"
#include <stdlib.h>
// Comparation for qsort in standard libary
int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}
/* buffer exch implemetion */
void exch(void *buf, int size, int i, int j)
{
	char *a = (char*)buf + i*size;
	char *b = (char*)buf + j*size;
	for (int k = 0; k < size; k++) {
		char tmp = a[k];
		a[k] = b[k];
		b[k] = tmp;
	}	
}

void qsort_2(void* a, int size, int l, int r, int (*compare)(const void*, const void*))
{
	int i = l-1, j = r;
	int p = l-1, q = r;
	if (r <= l) return;
	while (1) {
// From left, find the first element greater than
// or equal to v. This loop will definitely terminate
// as v is last element
		while (compare((char*)a +(++i)*size, (char*)a +(r)*size) < 0);
// From right, find the first element smaller than or
// equal to v
		while (compare((char*)a +(r)*size, (char*)a +(--j)*size) < 0)
			if (j == l)
				break;
 
// If i and j cross, then we are done
		if (i >= j) break;
 
// Swap, so that smaller goes on left greater goes on right
		exch(a, size, i, j);
  
// Move all same left occurrence of pivot to beginning of
// array and keep count using p
		if (compare((char*)a +(i)*size, (char*)a +(r)*size) == 0)
		{
			p++;
			exch(a, size, p, i);
		}
 
// Move all same right occurrence of pivot to end of array
// and keep count using q
		if (compare((char*)a +(j)*size, (char*)a +(r)*size) == 0)
		{
			q--;
			exch(a, size, j, q);
		}
	}
 
// Move pivot element to its correct index
	exch(a, size, i, r); 
// Move all left same occurrences from beginning
// to adjacent to arr[i]
	j = i-1;
	for (int k = l; k < p; k++, j--)
		exch(a, size, k, j);
 
// Move all right same occurrences from end
// to adjacent to arr[i]
	i = i+1;
	for (int k = r-1; k > q; k--, i++)
		exch(a, size, i, k);

//recursion
	qsort_2(a, size, l, j, compare);
	qsort_2(a, size, i, r, compare);
	
}
