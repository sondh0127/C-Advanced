#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "symtable.h"

#define INITIAL_SIZE 1
#define INCREMENTAL_SIZE 1


SymbolTable createSymbolTable(Entry(*makeNode)(void*, void*), int(*compare)(void*, void*))
{
	SymbolTable s;
	s.size = INITIAL_SIZE;
	s.total = 0;
	s.entries = (Entry*)malloc(INITIAL_SIZE*sizeof(Entry));
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
		entries[des] = book->makeNode(key, value);
		return;
	}
	if (book->total >= book->size) {
		/* Entry * new_entries = (Entry*)malloc(sizeof(Entry)*(book->size+ INCREMENTAL_SIZE)); */
		/* for(int i = 0; i < book->total; i++) { */
		/* 	new_entries[i] = entries[i]; */
		/* } */
		/* book->entries = new_entries; */
		/* free(entries); */
		/* entries = book->entries; */
		entries = (Entry*)realloc(entries, sizeof(Entry)*(book->size + INCREMENTAL_SIZE));
		book->size +=INCREMENTAL_SIZE;
		book->entries = entries;
	}
	int i;
	for(i = book->total - 1; (i >= 0 && book->compare(entries[i].key, key) > 0); i--) {
		entries[i+1] = entries[i];
	}
	entries[i+1] = book->makeNode(key,value);
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
