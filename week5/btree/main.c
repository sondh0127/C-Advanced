#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extio.h"
#include "../../lib/include/btree.h"

typedef struct Phone {
	char name[70];
	long phone;
}Phone;

void print_bterror(void)
{
    int errorcode, ioerr;
    char fname[ZRNAMESZ],msg[ZMSGSZ];
	
    btcerr(&errorcode,&ioerr,fname,msg);
    fprintf(stderr,"btsort: btree error (%d) [%s] - %s\n",
            errorcode,fname,msg);
}


void display_bt(BTA* rootBT){
	int val; //rsize
	long j = 0;
	/* status =bfndky(rootBT,"1",&val); */
	/* if(status==0){ */
	/* 	printf("1\n"); */
	/* 	j++; */
	/* } */
	
	int  size= sizeof(long);
	char name[100];
	char phone[100];
	btpos(rootBT, ZSTART); //ZSTART = 1; ZEND
	/* btpos for the key-> bnxtky(bprvky) (traverse) -> btsel
	 can set start at given key = bfndky
	 other func
	 Updating the value(not data of key) of a key
	 int bupdky(BTA* btact, char* key, BTint value); value = val, rsize

	 

Creating a root
int btcrtr(BTA* btact, char* root);
Changing the current root
int btchgr(BTA* btact, char* root);
Deleting a root
int btdelr(BTA* btact, char* root);

can use:
int btupd(BTA* btact, char* key, char* data, int dsize);

Updating data for an existing key

output: data
int btsel(BTA* btact, char* key, char* data, int dsize, int* rsize);

del a key and associated data
int btdel(BTA* btact, char* key);

	*/int btseln(BTA* btact, char* key, char* data, int dsize, int* rsize);


	while(btseln(rootBT, name, phone, size, &val) == 0) {
		printf("%15s\t %ld\n",  name, *(long*)phone);
		j++;	
	}
	printf("n = %ld", j);
}

int insert_address(BTA *rootBT) {
	int status ;
	char name[80];
	char phone[30]; // ZKYLEN
	printf("Type new phone: (Type \"quit\" for exit))\n");
	strcpy(name, "");
	while(1) {
		printf("Name(key): "); readLn(stdin, name, 80);
		if(strcmp(name, "quit") == 0) break;
		printf("Phone(value): "); readLn(stdin, phone, 30);
		if(strcmp(phone, "quit") == 0) break;
		status = btins(rootBT, name,(char*)(&phone), sizeof(long));
				
		if(status != 0) {
			printf("btree: btins: [error] Dulicape key \n");
		}
		printf("Return value: %d\n", status);
	}
	return status;
}


int menu() {
	int choose = 0;
	int MAX = 5;
	char menu[][40] = {"Insert a new address", "Find a entry", "Print all phone book" , "Delete an entry", "Save and exit"};

	printf("\n\t*=*=*=| PHONE ADDRESS |=*=*=*\n");
	printf("  \t=========== MENU =========== \n");
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

int main(int argc, char *argv[argc])
{
	if(argc != 2) {
		printf("btree: usage: btree filename\n");
		exit(1);
	}
	char *filename = argv[1];
	btinit();
	BTA *rootBT;
	
	/* open file if file doesn't exist => create new file*/
	if((rootBT = btopn(filename, 0, FALSE))!= NULL) {
		printf("Open file successful!\n");
	} else {
		rootBT = btcrt(filename, 0, FALSE);
        fprintf(stderr,"Unable to open %s btree index.\n Create new instead\n", filename);
    }

	char name[80];
	char phone_s[32]; // ZKYLEN
	
	int choose = 0;
	int val;//*rsize
	int status;
	int size_l = sizeof(long);
	do {
		choose = menu();
		
		switch (choose) {
		case 1:
			//
			break;
		case 2:
			printf("Find address: \n");
			printf("Name(key): "); readLn(stdin, name, 70);
			//find
			status = bfndky(rootBT, name, &val);
			btsel(rootBT, name, phone_s, size_l, &val);
			
			printf("%s\t %ld\n",  name, *(long*)phone_s);
			printf("Return value: %d\n", status);
			break;
		case 3:
			display_bt(rootBT);
			break;
		case 4:
			printf("Delete key: (Type \"quit\" for exit)\n");
			strcpy(name, "");
			while(1) {
				printf("Name(key): "); readLn(stdin, name, 70);
				if(strcmp(name, "quit") == 0) break; // exit the loop
				status = btdel(rootBT, name);
				//int bdelky(BTA* btact, char* key); only key del
				if(status != 0) {
					printf("Cant find this key %s\n", name);
				}
				printf("Return value: %d\n", status);
			}
			break;
		case 5:
			btcls(rootBT);
			break;
		case 6:
			/* printf("Type new phone: (Type \"q\" for exit))\n"); */
			/* strcpy(name, ""); */
			/* while(1) { */
			/* 	printf("Name(key): "); readLn(stdin, name, 70); */
			/* 	if(strcmp(name, "q") == 0) break; */
			/* 	printf("Return value: %d\n", status); */
			/* 	printf("Phone(value): "); scanf("%ld", &phone); */
			/* 	status = binsky(rootBT, name, 0); */
			/* 	status = btins(rootBT, name,(char*)(&phone), size_l); */
			/* 	if(status != 0) { */
			/* 		printf("btree: binsky: [error] Cant find this key - Create new key\n"); */
			/* 		status = btins(rootBT, name,(char*)(&phone), size_l); */
			/* 		//printf("Return value: %d\n", status); */
			/* 	} else { */
					
			/* 	} */
				
				
			/* } */	
			break;
		
		default:
			printf("Wrong choose: (1- 5)\n");
			break;
		}
	} while (choose != 5);
    return 0;
}
