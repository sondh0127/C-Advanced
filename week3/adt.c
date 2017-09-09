#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "adt.h"
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

PhoneBook createPhoneBook()
{// Create new Phone Book
	PhoneBook p;
	p.total = -1;
	p.size = INITIAL_SIZE;
	p.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry)*INITIAL_SIZE);
	return p;
}

void dropPhoneBook(PhoneBook* book)
{// remove all Phone Book
	free(book->entries);
}

int binarySearch(PhoneEntry* entries, int l, int r, char* name, int* found)
{

	if (r >= l)
	{
		int mid = l + (r - l)/2;
		if(strcmp(entries->name, name) == 0 ) {
			*found = 1;
			return mid;
		} 

		if(strcmp(entries->name, name) > 0)
		{
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
	int i = binarySearch(Entry, 0, book->total - 1, name, &found);
	if(found == 1)
	{
		strcpy(Entry[i].name, name);
		Entry[i].number = number;
	}
	else //memcpy
	{
		book->total++;
		if(book->total >= book->size) {
			Entry = (PhoneEntry*)realloc(Entry, sizeof(PhoneEntry)*(INITIAL_SIZE + INCREMENTAL_SIZE));
			book->size += INCREMENTAL_SIZE;
		}
		else if(book->total > INITIAL_SIZE + INCREMENTAL_SIZE) {
			printf("added failed, No more space!\n");
			return;
		}
		strcpy(Entry[book->total].name, name);
		Entry[book->total].number = number;
	}
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
