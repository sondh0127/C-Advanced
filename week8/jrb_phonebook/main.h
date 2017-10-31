#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/include/jrb.h"
#include "../../lib/include/btree.h"

/* MAIN'S PROTOTYPE*/
int menu();

typedef struct {
	char name[70];
	char phone[20];
} Phone;

void getData(char *filename, JRB book);
void insertPhone(JRB book);
void showPhone(JRB book);
void deletePhone(JRB book);
void modifyPhone(JRB book);
void saveData(char *filename, JRB book);


#endif /* MAIN_H */
