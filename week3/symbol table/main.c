#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "symtable.h"

int main()
{	SymbolTable phoneBook = createSymbolTable(makePhone, comparePhone);
	long number = 983984775;
	char name[] = "Tuan Anh";
	addEntry(name, &number, &phoneBook);
	
	number = 909775090;
	strcpy(name, "Do Lam");
	addEntry(name, &number, &phoneBook);
	
	number = 959494944;
	strcpy(name,"Tuan Dung");
	addEntry(name, &number, &phoneBook);
	
	number = 927759292;
	strcpy(name,"Anh Thang");
	addEntry(name, &number, &phoneBook);
	
	number =  917759191;
	strcpy(name,"Ngo Phong");
	addEntry(name, &number, &phoneBook);

	//name = "Ngo Phong"
	number =  947759494;
	addEntry(name, &number, &phoneBook);

	
	
	for (int i = 0; i < phoneBook.total; i++) {
		printf("%d|%s\t%d\n", i+1, (char*)phoneBook.entries[i].key, *((int*)phoneBook.entries[i].value));
	}
    return 0;
}
