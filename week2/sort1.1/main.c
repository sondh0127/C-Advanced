#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SMALL_NUMBER 20
#define HUGE_NUMBER 1000000

#include "sort.h"

int* createArray(int size);
int* dumpArray(int *p, int size);

void printarr(int a[], int size);
void measuretime(void(*f)(int*, int, int), int a[], int size);

int main()
{
	int *a1, *a2;
	a1 = createArray(SMALL_NUMBER);
	a2 = dumpArray(a1, SMALL_NUMBER);

	printf("Initial\n");
	printarr(a1, SMALL_NUMBER);
	printarr(a2, SMALL_NUMBER);
	
	printf("After sorting\n");
	qsort_2(a1, sizeof(int), 0, SMALL_NUMBER-1, compare);
	/* print data in a1 */
	printarr(a1, SMALL_NUMBER);
	
	qsort(a2, SMALL_NUMBER, sizeof(int), compare);
	/* print data in a2 */
	printarr(a2, SMALL_NUMBER);
	
	free(a1);
	free(a2);
	
	a1 = createArray(HUGE_NUMBER);
	a2 = dumpArray(a1, HUGE_NUMBER);
	
	clock_t start, end;
	double time_taken;
	printf("Quick Sort qsort_2\n");
	start = clock();
  	//function test	
	qsort_2(a1, sizeof(int), 0, HUGE_NUMBER - 1, compare);
	end = clock();
	time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\tRun time: %.2lf seconds \n",time_taken);

	
	printf("Quick Sort qsort built-in\n");

	start = clock();
  	//function test	
	qsort(a2, HUGE_NUMBER, sizeof(int), compare);
	end = clock();
	time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\tRun time: %.2lf seconds \n",time_taken);
	free(a1);
	free(a2);

	
    return 0;
}

// A utility function to print an array
void printarr(int a[], int size) {
	printf("Show Array: ");
	for (int i = 0; i < size; i++)
		printf("%d  ", a[i]);
	printf("\n");
}

void measuretime(void(*f)(int*, int, int), int a[], int size)
{
	clock_t start, end;

	start = clock();
  	//function test	
	(*f)(a, 0, size-1);
	end = clock();
	double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Run time: %.2f seconds \n",time_taken);
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

int* dumpArray(int *p, int size) {
	int* a = (int*)malloc(size * sizeof(int));
	memcpy(a, p, size* sizeof(int));
	return a;
}
