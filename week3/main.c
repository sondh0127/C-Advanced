// The rule: type everything from slide first
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "adt.h"

int main()
{
	PhoneBook book;
//Khoi tao & chen
	book = createPhoneBook();
	addPhoneNumber("Do Lam", 909090, &book);
	addPhoneNumber("Tuan Dung", 929292, &book);
	addPhoneNumber("Do Lam", 999999, &book);
	addPhoneNumber("Anh Thang", 919191, &book);
	addPhoneNumber("Ngo Phong", 949494, &book);
//Hien thi danh sach book
	for (int i = 0; i < book.total + 1; i++) {
		printf("%d|%s\t|%ld\n", i+1, book.entries[i].name,  book.entries[i].number);
	}
//Tim kiem
	
	PhoneEntry* entry = getPhoneNumber("Do Lam", book);
	if(entry == NULL)
		printf("Can not found!\n");
	else
		printf("%ld\n", entry->number);
	return 0;
}
