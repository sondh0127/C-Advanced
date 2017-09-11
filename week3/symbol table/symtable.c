#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "symtable.h"
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10


SymbolTable createSymbolTable(Entry(*makeNode)(void*, void*), int(*compare)(void*, void*))
{
	SymbolTable s;
	s.entries = (Entry*)malloc(INITIAL_SIZE*sizeof(Entry));
	s.total = 0;
	s.size = INITIAL_SIZE;
	s.makeNode = makeNode;
	s.compare = compare;
	s.makeNode = makeNode; 
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
		if(res == 0 ) {
			*found = 1;
			return mid;
		} 

		if(res > 0)
		{
			*found = 0;
			return binarySearch(entries, l, mid -1, compare, key, found);
		}

		return binarySearch(entries, mid + 1, r, compare, key, found);

	}
	return -1;
}
void addEntry(void *key, void *value, SymbolTable* book)
{
	Entry *entries = book->entries;
	int found = 0;
	int i = binarySearch(entries, 0, book->size -1 , book->compare, key, &found);
	if(found == 1)
	{
		
		entries[i].key = strdup((char*)key);
		entries[i].value = strdup((char*)value);
		/* memcpy(entries[i].key, key,strlen((char*)key)+1); */
		/* memcpy(entries[i].value, value, strlen((char*)value)+1); */
	}
	else //memcpy
	{
		book->total++;
		if(book->total >= book->size) {
			entries = (Entry*)realloc(entries, sizeof(Entry)*(INITIAL_SIZE + INCREMENTAL_SIZE));
			book->size += INCREMENTAL_SIZE;
		}
		else if(book->total > INITIAL_SIZE + INCREMENTAL_SIZE) {
			printf("added failed, No more space!\n");
			return;
		}
		entries[book->total - 1].key = strdup((char*)key);
		entries[book->total - 1].value = strdup((char*)value);
		/* memcpy(entries[book->total - 1].key, key,strlen((char*)key)+1); */
		/* memcpy(entries[book->total - 1].value, value,strlen((char*)value)+1); */
	}
}
Entry* getEntry(void *key, SymbolTable book)
{
	int found = 0;
	int pos = binarySearch(book.entries, 0, book.size -1 , book.compare, key, &found);
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
