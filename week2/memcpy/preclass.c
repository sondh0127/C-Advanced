#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SMALL_NUMBER 20

void *memcpy(void * region1, const void* region2, size_t n)
{
	const char* first = (const char*) region2;
	const char* last = ((const char*) region2) + n;
	char* result = (char*) region1;
	while(first != last)
		*result++ = *first++;
	return result;
}
/*
  address
  size_t
 */
// PC = Pointer constant = khong cho phep thay doi dia chi
//int x = 5;
//int* const p = &x;
// CP = constant Pointer = khong cho phep thay doi gia tri
//const int* q;

int int_compare(void const* x, void const *y) {
	return (*(int*)x - *(int*)y);
}

// return -1 if not found

int search(void *buf, int size, int l, int r, void *item,
		   int(*int_compare)(void const*, const void*))
{
	int i, res;
	if(r < l ) return -1;
	i = (l + r)/2;
	res = int_compare(item, (char*)buf+(size*i));
	if(res == 0)
		return i;
	else if (res < 0)
		return search(buf, size, l, i - 1, item, int_compare);
	else
		return search(buf, size, i + 1, r, item, int_compare);
}
int* createArray(int size) {

	// seed for random input
	srand(time(NULL));
	int* a = (int*)malloc(size * sizeof(int));
	for(int i = 0; i < size; i++) {
		a[i] = 1 + rand() % 100;
	}
	return a;
}

// A utility function to print an array
void printarr(int a[], int size) {
	qsort
	for (int i = 0; i < size; i++)
		printf("%d  ", a[i]);
	printf("\n");
}

int main()
{
	printf("%s\n", );
    int *a1 = createArray(SMALL_NUMBER);
	printarr(a1, SMALL_NUMBER);
	int item = a1[0];
	qsort(a1, SMALL_NUMBER, sizeof(int), int_compare);

	printarr(a1, SMALL_NUMBER);


	int res = search(a1, sizeof(int), 0, SMALL_NUMBER -1, &item, int_compare);

	printf("Gia tri cua res = %d\n", res);
	free(a1);
    return 0;
}

