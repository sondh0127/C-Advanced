#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "extio.h"
#include "main.h"
#include "../../lib/include/jrb.h"
#include "../../lib/include/btree.h"

#define MAX_LEN 255


/* MAIN */
int main(int argc, char *argv[])
{
	if(argc != 2) {
		printf("Usage: main filename\n");
		exit(1);
	}
	char *filename = strdup(argv[1]);
	btinit();
	BTA *root = btopn(filename, 0, FALSE);
	
	/* open file if file doesn't exist => create new file*/
	if(root != NULL) {
		printf("Open file successful!\n");
	} else {
		root = btcrt(filename, 0, FALSE);
        fprintf(stderr,"Unable to open %s btree index.\n Create new instead\n", filename);
    }
 
	int choose = 0;
	do {
		choose = menu();
		switch (choose) {
		case 1:
			insertAddress(root);
			break;
		case 2:
			findAddress(root);
			break;
		case 3:
			displayRoot(root);
			break;
		case 4:
			deleteAddress(root);
			break;
		case 5:

			btcls(root);
			printf("Good Bye!\n");
			break;
		default:
			printf("Invalid input! Type (1-5)\n");
			break;	
		}
	}  while (choose !=5);
	return 0;
}

/* FUNCTION DEF */
int menu() {
	int choose = 0;
	int MAX = 5;
	char menu[][40] = { "Insert a new address", 
						"Find a entry", 
						"Print all phone book", 
						"Delete an entry" , 
						"Save and exit"};

	printf("\n\t================================\n");
	printf(  "\t============| MENU |============\n");
	printf(  "\t================================\n");
	for(int i = 0; i < MAX; i++)
		printf("\t%d. %s\n", i+1, menu[i]);
	printf("Enter your chose: ");
	while(scanf("%d", &choose) != 1) {
		printf("Input must be integer!\n");
		while (getchar() != '\n' );
		//wasting the buffer till the next new line
		printf("Enter your choose: ");
	}
	return choose;	
}

void insertAddress(BTA *root) 
{
	char phone_ptr[32];
	int status;
	int val;
	int size_l = sizeof(long);

	Phone *p = (Phone *) malloc(sizeof(Phone));
	printf("Insert new address (Type new name and phone)\n");
	printf("Name: "); readLn(stdin, p->name, 70);

	status = bfndky(root, p->name, &val);
	printf("%d\n", val);
	// found return 0
	if (status != 0) {
		printf("Phone: "); scanf("%ld", &p->phone);
		status = btins(root, p->name, (char *)(&(p->phone)), size_l);
	} else {
		printf("This key %s is exist\n", p->name);
	}

	//find
	status = bfndky(root, p->name, &val);
	btsel(root, p->name, phone_ptr, size_l, &val);

	printf("%s\t %ld\n",  p->name, *(long*)phone_ptr);
	printf("Return value: %d\n", status);
	printf("Insert successful\n");
}

void findAddress(BTA *root)
{
	Phone *p = (Phone *) malloc(sizeof(Phone));
	char phone_ptr[32];
	int status;
	int val;
	int size_l = sizeof(long);
	printf("Find address (Type name)\n");
	printf("Name: ");	readLn(stdin, p->name, 70);

	//find
	status = bfndky(root, p->name, &val);
	btsel(root, p->name, phone_ptr, size_l, &val);
	
	printf("%s\t %ld\n",  p->name, *(long*)phone_ptr);
	printf("Return value: %d\n", status);
}

void displayRoot(BTA* root)
{
	Phone *p = (Phone *) malloc(sizeof(Phone));
	char phone_ptr[32];
	int val;
	int  size_l= sizeof(long);
	long count = 0;
	btpos(root, ZSTART); //ZSTART = 1; ZEND
	while(btseln(root, p->name, phone_ptr, size_l, &val) == 0) {
		printf("%15s\t %ld\n",  p->name, *(long*)phone_ptr);
		count++;	
	}
	printf("n = %ld", count);
}

void deleteAddress(BTA *root)
{
	Phone *p = (Phone *) malloc(sizeof(Phone));
	int status;
	printf("Delete key: (Type key name)\n");
	printf("Name: "); readLn(stdin, p->name, 70);
	status = btdel(root, p->name);
//int bdelky(BTA* btact, char* key); only key del
	if(status != 0) {
		printf("Cant find this key %s\n", p->name);
	}
	printf("Return value: %d\n", status);
}