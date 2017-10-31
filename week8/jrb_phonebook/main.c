#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extio.h"
#include "main.h"
#include "../../lib/include/jrb.h"
#include "../../lib/include/btree.h"

#define MAX_LEN 255


/* MAIN */
int main(int argc, char const *argv[])
{
	if(argc != 2) {
		printf("Usage: main filename\n");
		exit(1);
	}
	char *filename = strdup(argv[1]);

	JRB book = make_jrb();
	// VARIABLE
	int choose = 0;
	do {
		choose = menu();
		switch (choose) {
		case 1:
			getData(filename, book);
			break;
		case 2:
			insertPhone(book);
			break;
		case 3:
			showPhone(book);
			break;
		case 4:
			deletePhone(book);
			break;
		case 5:
			modifyPhone(book);
			break;
		case 6:
			saveData("phonebook_mdf.txt", book);
			jrb_free_tree(book);
			printf("Good Bye!\n");
			break;
		default:
			printf("Invalid input! Type (1-5)\n");
			break;	
		}
	}  while (choose != 6);
	return 0;
}

/* FUNCTION DEF */
int menu() {
	int choose = 0;
	int MAX = 6;
	char menu[][40] = { "Create a phone book",
						"Insert a new entry", 
						"Print phone book", 
						"Delete an entry" ,
						"Modify a number",
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
// FUNCTION

void getData(char *filename, JRB book)
{
	FILE *fp = fopen(filename,"r");
	if (fp== NULL){
		fprintf(stderr, "Error: Cant opening file");
		exit(1);
	}
	JRB ptr;
	Phone p;
	while(feof(fp) == 0) {
		fscanf(fp, "%[^\t]\t%[^\n]\n", p.name, p.phone);
		printf("%s\t%s\n", p.name, p.phone);
		if(strcmp(p.name, "") != 0) {
			ptr = jrb_find_str(book, p.name);
			if(ptr == NULL) {
				ptr = jrb_insert_str(book, strdup(p.name), new_jval_s(strdup(p.phone)));
			} else {
				// printf("Dulicape key!\n");
			}
		}
	}
	fclose(fp);
	printf("\n=>Input successful!\n");
}

void insertPhone(JRB book) {
	JRB ptr;
	Phone p;
	printf("Insert new phone (Type new name and phone)\n");
	printf("Name: "); readLn(stdin, p.name, 70);
	ptr = jrb_find_str(book, p.name);
	if (ptr == NULL) {
		printf("Phone: "); readLn(stdin, p.phone, 20);
		ptr = jrb_insert_str(book, strdup(p.name), new_jval_s(strdup(p.phone)));
	} else {
		printf("Name already exists!\n");
	}
}

void showPhone(JRB book)
{
	JRB ptr;
	printf("\n====PHONE BOOK====\n");
	jrb_traverse(ptr, book) {
		printf("%s\t%s\n", jval_s(ptr->key), jval_s(ptr->val));
	}
	printf("====================\n");
}

void deletePhone(JRB book) 
{
	JRB ptr;
	Phone p;
	printf("Delete phone (Type key name)\n");
	printf("Name: "); readLn(stdin, p.name, 70);
	ptr = jrb_find_str(book, p.name);
	if (ptr != NULL) {
		jrb_delete_node(ptr);
		printf("Delete successfully\n");
	} else {
		printf("Can't find phone name!\n");
	}
}

void modifyPhone(JRB book)
{
	JRB ptr;
	Phone p;
	printf("Modify phone (Type key name)\n");
	printf("Name: "); readLn(stdin, p.name, 70);
	ptr = jrb_find_str(book, p.name);
	if (ptr != NULL) {
		jrb_delete_node(ptr);
		printf("Type new phone name: "); readLn(stdin, p.phone, 20);
		ptr = jrb_insert_str(book, strdup(p.name), new_jval_s(strdup(p.phone)));
	} else {
		printf("Can't find phone name!\n");
	}
}

void saveData(char *filename, JRB book)
{
	JRB ptr;
	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Can't open file, %s\n", filename);
		exit(1);
	}
	if(book == NULL)
		return;
	jrb_traverse(ptr, book) {
		fprintf(fp, "%s\t%s\n", jval_s(ptr->key), jval_s(ptr->val));
	}

	fclose(fp);
}