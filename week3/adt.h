#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct {
	//Ten - sdt
	char name[80];
	long number;
}PhoneEntry;

typedef struct {
	// address book
	// cap phat dong dua tren so luong toi da cac cap(entity)
	PhoneEntry *entries;
	int total;
	int size;
}PhoneBook;

PhoneBook createPhoneBook()
{// Create new Phone Book
	PhoneBook p;
	p.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry));
	p.total = 0;
	p.size = 0;
	return p;
}

void dropPhoneBook(PhoneBook* book)
{// remove all Phone Book
	free(book->entries);
	book->size = 0;
}

void addPhoneNumber(char* name, long number, PhoneBook* book)
{// add new PhoneNumber-Person(overwrite)
	
}
PhoneEntry *getPhoneNumber(char* name, PhoneBook book)
{// find an entity from Phone Book return NULL if this entry can not find.
	return NULL;
}





