#ifndef SYMTABLE_H
#define SYMTABLE_H
typedef struct {
	void *key;
	void *value;
}Entry;

typedef struct {
	Entry *entries;
	int size, total;
	Entry(*makeNode)(void*, void *);
	int(*compare)(void*, void*);
}SymbolTable;

int comparePhone(void* key1, void* key2);
Entry makePhone(void* name, void* phone);

SymbolTable createSymbolTable(Entry(*makeNode)(void*, void*), int(*compare)(void*, void*));
void dropSymbolTable(SymbolTable *tab);
void addEntry(void *key, void *value, SymbolTable* book);
Entry* getEntry(void *key, SymbolTable book);

void qsort_2(void* a, int size, int l, int r, int (*compare)(void*, void*));

#endif /* SYMTABLE_H */

