#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "symtable.h"

#define INITIAL_SIZE 0
#define INCREMENTAL_SIZE 10


SymbolTable createSymbolTable(Entry(*makeNode)(void*, void*), int(*compare)(void*, void*))
{
	SymbolTable s;
	s.size = INITIAL_SIZE;
	s.total = 0;
	s.entries = (Entry*)malloc(s.size*sizeof(Entry));
	s.makeNode = makeNode;
	s.compare = compare;
	return s;
}
void dropSymbolTable(SymbolTable *tab)
{
	free(tab->entries);
	tab->total = 0;
	tab->size = 0;
}

int binarySearch(Entry* entries, int l, int r,int(*compare)(void*, void*), void *key, int* found)
{
	if (r >= l)
	{
		int mid = l + (r - l)/2;
		
		int res = compare(entries[mid].key, key);
		if (res == -1) return -1; 
		if(res == 0) {
			*found = 1;
			return mid;
		} 

		if(res > 0)
		{
			*found = 0;
			return binarySearch(entries, l, mid -1, compare, key, found);
		}
		*found = 0;
		return binarySearch(entries, mid + 1, r, compare, key, found);

	}
		return -1;
}
void addEntry(void *key, void *value, SymbolTable* book)
{
	Entry *entries = book->entries;
	
	int found = 0;
	int des = binarySearch(entries, 0, book->total - 1, book->compare, key, &found);
	//printf("%d\n", found);
	if(found == 1)
	{
		
		//entries[i].key = strdup((char*)key);
		//entries[des].value = strdup((char*)value);
		return;
		/* memcpy(entries[i].key, key,strlen((char*)key)+1); */
		memcpy(entries[des].value, value, strlen((char*)value)+1);
	}
	/* if(book->total >= book->size) {  */
	/* 	entries = (Entry*)realloc(entries, sizeof(Entry)*(INITIAL_SIZE + INCREMENTAL_SIZE)); */
	/* 	book->size += INCREMENTAL_SIZE; */
	/* } */
	/* else if(book->total > INITIAL_SIZE + INCREMENTAL_SIZE) { */
	/* 	printf("added failed, No more space!\n"); */
	/* 	return; */
	/* } */
	int i;
	for(i = book->total - 1; (i >= 0 && book->compare(entries[i].key, key) > 0); i--) {
		entries[i+1].key = strdup(entries[i].key);
		entries[i+1].value = strdup(entries[i].value);
	}
	entries[i+1].key = strdup((char*)key);
	entries[i+1].value = strdup((char*)value);
	book->total++;

	
}


Entry* getEntry(void *key, SymbolTable book)
{
	int found = 0;
	int pos = binarySearch(book.entries, 0, book.total -1 , book.compare, key, &found);
	if(found == 1) {
		return &book.entries[pos];
	}
	else
		return NULL;
}
// Phone data type
// makePhone
Entry makePhone(void* name, void* phone) {
	Entry res;
	/* char *strdup(const char *src) { */
    /* size_t len = strlen(src) + 1; */
    /* char *s = malloc(len); */
    /* if (s == NULL) */
    /*     return NULL; */
    /* return (char *)memcpy(s, src, len); */
/* } */
	res.key = strdup((char*)name);
	res.value = malloc(sizeof(long));
	memcpy(res.value, phone, sizeof(long));
	return res;
}
//compare
int comparePhone(void* key1, void* key2) {
	if(key1 != NULL)
		return strcmp((char*)key1, (char*)key2);
	else
		return -1;
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
