#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "adt.h"
#define INITIAL_SIZE 1
#define INCREMENTAL_SIZE 1

PhoneBook createPhoneBook()
{// Create new Phone Book
	PhoneBook p;
	p.total = 0;
	p.size = INITIAL_SIZE;
	p.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry)*INITIAL_SIZE);
	return p;
}

void dropPhoneBook(PhoneBook* book)
{// remove all Phone Book
	free(book->entries);
	book->total = 0;
	book->size = 0;
}

int binarySearch(PhoneEntry* entries, int l, int r, char* name, int* found)
{

	if (r >= l) {
		int mid = l + (r - l)/2;
		if(strcmp(entries[mid].name, name) == 0 ) {
			*found = 1;
			return mid;
		} 

		if(strcmp(entries[mid].name, name) > 0) {
			*found = 0;
			return binarySearch(entries, l, mid -1, name, found);
		}

		return binarySearch(entries, mid + 1, r, name, found);

	}
	return -1;
}

void addPhoneNumber(char* name, long number, PhoneBook* book)
{// add new PhoneNumber-Person(overwrite)
	PhoneEntry *Entry = book->entries;
	int found = 0;
	int pos = binarySearch(Entry, 0, book->total - 1, name, &found);
	if(found == 1)
	{
		//Strcpy(Entry[i].name, name);
		Entry[pos].number = number;
		return;
	}

	if(book->total >= book->size) {
		/* PhoneEntry * new_entries = (PhoneEntry*)malloc(sizeof(PhoneEntry)*(book->size+ INCREMENTAL_SIZE)); */

		/* for(int i = 0; i < book->total; i++) { */
		/* 	new_entries[i] = Entry[i]; */
		/* } */
		/* book->entries = new_entries; */
		/* free(Entry); */
		/* Entry = book->entries; */
		Entry = (PhoneEntry*)realloc(Entry, sizeof(PhoneEntry)*(book->size+INCREMENTAL_SIZE));
		book->size +=INCREMENTAL_SIZE;
	}
	
	int i;
	for(i = book->total - 1; (i >= 0 && strcmp(Entry[i].name, name) > 0); i--) {
		Entry[i+1] = Entry[i];
	}
	strcpy(Entry[i+1].name, name);
	Entry[i+1].number = number;
	book->total++;


}
PhoneEntry *getPhoneNumber(char* name, PhoneBook book)
{// find an entity from Phone Book return NULL if this entry can not find.
	int found = 0;
	int pos = binarySearch(book.entries, 0, book.total - 1, name, &found);
	if(found == 1) {
		return &book.entries[pos];
	}
	else
		return NULL;
}
