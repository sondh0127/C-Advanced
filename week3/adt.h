#ifndef ADT_H
#define ADT_H
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

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);

int binarySearch(PhoneEntry* entries, int l, int r, char* name, int* found);
void addPhoneNumber(char* name, long number, PhoneBook* book);
PhoneEntry *getPhoneNumber(char* name, PhoneBook book);



#endif /* ADT_H */








