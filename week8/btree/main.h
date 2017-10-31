#ifndef MAIN_H
#define MAIN_H
#include "../../lib/include/jrb.h"
#include "../../lib/include/btree.h"

typedef struct Phone {
	char name[70];
	long phone;
} Phone;

/* MAIN'S PROTOTYPE*/
int menu();
void insertAddress(BTA *root) ;
void findAddress(BTA *root);
void displayRoot(BTA* root);
void deleteAddress(BTA *root);

#endif /* MAIN_H */
