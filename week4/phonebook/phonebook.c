#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extio.h"
#include "../../lib/include/jrb.h"
#include "phonebook.h"
#define MENUOPT 6

int main() {
	char menu[MENUOPT][40] = {"Create a phone book", "Insert a new entry", "Print phone book", "Delete an entry", "Modify a number", "Save and exit"};
	char *filename = "phonebook.txt";
	JRB b = make_jrb();
	JRB ptr = NULL;

	Phone p;
	int choose = 0;
	do {
		getMenu(menu, MENUOPT);
		
		printf("Enter your chose: ");
		while(scanf("%d", &choose) != 1) {
			printf("Input must be integer!\n");
			while (getchar() != '\n' );
			//wasting the buffer till the next new line
			printf("Enter your choose: ");
		}
		switch (choose) {
		case 1:
			
			getData(filename, b, ptr);
			printf("Input successful!\n");
			break;
		case 2:
            printf("Type new phone:\n");
			printf("Name: "); readLn(stdin, p.name, 70);
			ptr = jrb_find_str(b, p.name);			
			if(ptr == NULL) {
				printf("Phone: "); readLn(stdin, p.phone, 20);
				ptr = jrb_insert_str(b, strdup(p.name), new_jval_s(strdup(p.phone)));
			} else {
				printf("\nDulicape Key\n");
			}
			break;
		case 3:
        	jrb_traverse(ptr, b) {
				printf("%s\t%s\n",jval_s(ptr->key), jval_s(ptr->val));
			}
			break;
		case 4:
		   	printf("Delete phone:\n");
			printf("Name(key): "); readLn(stdin, p.name, 70);
			ptr = jrb_find_str(b, p.name);
			if(ptr != NULL) {
				jrb_delete_node(ptr);
				printf("Delete successfully\n");
			} else {
				printf("Can't find the key!\n");
			}    	
			break;
		case 5:
			printf("Modify phone:\n");
			printf("Name(key): "); readLn(stdin, p.name, 70);
			ptr = jrb_find_str(b, p.name);
			if(ptr != NULL) {
                jrb_delete_node(ptr);
				printf("Type new phone number:\nPhone: "); readLn(stdin, p.phone, 20);
				ptr = jrb_insert_str(b, strdup(p.name), new_jval_s(strdup(p.phone)));
			} else {
				printf("Can't find the key!\n");
			}    	
			break;
		case 6:
            saveData("phonebook_mdf.txt", b, ptr);
			printf("Saved and exited\n");
			jrb_free_tree(b);
			break;
		default:
            printf("Choise must be from 1 to 6\n");
			break;
		}
	} while (choose != 6);
 
	return 0;
}
void getMenu(char menu[][40], int len) {
	printf("\n\t\t===MENU===\n");
	for(int i = 0; i < len; i++)
        printf("\t%d. %s\n", i+1, menu[i]);     
}

void getData(char *filename, JRB b, JRB ptr) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Can't open file, %s\n", filename);
		exit(1);
	}
	Phone *p = (Phone*)malloc(sizeof(Phone));
	while(!feof(fp)) {
		fscanf(fp, "%70[^\t]\t%20[^\n]\n", p->name, p->phone);
		printf("%s\t%s\n",p->name, p->phone);
		ptr = jrb_find_str(b, p->name);
		if(ptr == NULL) {
			ptr = jrb_insert_str(b, strdup(p->name), new_jval_s(strdup(p->phone)));	
		} else {
			printf("Dulicape key!\n");
		}
	}
	free(p);
	fclose(fp);
}

void saveData(char *filename, JRB b, JRB ptr) {
	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Can't open file, %s\n", filename);
		exit(1);
	}
	if(b == NULL)
		return;
	jrb_traverse(ptr, b) {
		fprintf(fp, "%s\t%s\n", jval_s(ptr->key), jval_s(ptr->val));
	}

	fclose(fp);
}

