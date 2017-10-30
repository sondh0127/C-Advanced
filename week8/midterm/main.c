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
	
	/* open file if file doesn't exist => create new file*/
	

	int choose = 0;
	do {
		choose = menu();
		switch (choose) {
		case 1:
			
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			
			break;
		case 5:
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
	char menu[][40] = { "Search", 
						"Add", 
						"Delete", 
						"Print lastest word" , 
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