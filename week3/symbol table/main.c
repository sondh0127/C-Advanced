#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "symtable.h"

int comparePhone(void* key1, void* key2);
Entry makePhone(void* name, void* phone);

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

	
	/* printf("%d %d %s\n", phoneBook.size,phoneBook.total, (char*)phoneBook.entries->key); */
	for (int i = 0; i < phoneBook.total; i++) {
		printf("%d|%s\t%d\n", i+1, (char*)(phoneBook.entries[i].key), *((int*)(phoneBook.entries[i].value)));
	}
	dropSymbolTable(&phoneBook);
    return 0;
}

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
