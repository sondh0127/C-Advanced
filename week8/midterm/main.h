#ifndef MAIN_H
#define MAIN_H
#include "../../lib/include/jrb.h"
typedef struct {
	char domain[100];
	char ip[100];
} DNS;
/* MAIN'S PROTOTYPE*/
int menu();
void display_test(JRB dns);
void readFile(char *filename, JRB dns);
void insertDNS(JRB dns);
void saveData(char *filename, JRB dns);
JRB check_ip(JRB dns, char *ip);
void findIP(JRB dns);
void findDomain(JRB dns);
#endif /* MAIN_H */
