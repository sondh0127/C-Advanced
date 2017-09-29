#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/btree/btree.h"
#include "extio.h" 				/* import readLn (func for reading input) */

#include "dict.h"
#define MAX_LEN 100000

int menu() {
	int choose = 0;
	int MAX = 5;
	char menu[][40] = {"Add", "Find", "Print" , "Delete", "Save and exit"};

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
void display_bt(BTA* rootBT);

int main()
{
	char *filetxt = "anhviet109K.txt";
	char *fileDict = "dict.dat";
	char *fileSoundex = "soundex.dat";
	BTA *rootDic;
	BTA *soundexT;
	int status, val;
	btinit();
	/* open file if file doesn't exist => create new file*/
	rootDic = btopn(fileDict, 0, FALSE);
	if(rootDic != NULL) {
		printf("Open file successful!\n");
	} else {
		printf("Creating data\n");
		rootDic = btcrt(fileDict, 0, FALSE);
		/* import, creating data from .txt; */
		createDict(filetxt, &rootDic);
	}
	
	if((soundexT = btopn(fileSoundex, 0, FALSE))!= NULL) {
		printf("Open file successful!\n");
	} else {
		printf("Creating data\n");
		/* copy rootDic to soundexT for sug */
		createSoundexTree(rootDic, &soundexT);
	}
	int choose = 0;
	char word[MAX_LEN];
	char mean[MAX_LEN];
	char mean_out[MAX_LEN];
	int i,k;
	char suggest[15][100];
	do {
		choose = menu();
		
		switch (choose) {
		case 6:
			/* test case : suggestion word */
			printf("nhap tu can goi y:\n"); readLn(stdin, word, MAX_LEN);
			
			k = suggestion(soundexT,word,suggest);
			if(k!=0)
				for(i=0;i<k;i++) printf("%s\n",suggest[i]);
			break;
		case 1:
			printf(" Input data:\n");
			printf("word:");  readLn(stdin, word, MAX_LEN);
			printf("meaning:");  readLn(stdin, mean, MAX_LEN);
			printf("%15s\t %15s\n",  word, mean);
			status = btins(rootDic, word, mean, sizeof(char)*strlen(mean));
            btsel(rootDic, word, mean_out, sizeof(char)*MAX_LEN, &val);
			printf("%15s\t %15s\n",  word, mean_out);
			break;
		case 2:
			printf(" Input data:\n");
			printf("word:");  readLn(stdin, word, MAX_LEN);
			status = bfndky(rootDic, word, &val);
			if (status != 0)
				printf("Duplicate \n");
			break;

		case 3:
			display_bt(rootDic);
			break;
		case 4:
			printf(" Input data:\n");
			printf("word:");  readLn(stdin, word, MAX_LEN);
			status = btdel(rootDic, word);
			
			//just for test 
			if(status == 0)
			{
				btsel(rootDic, word, mean_out, sizeof(char)*MAX_LEN, &val);
				printf("%15s\t %15s\n",  word, mean_out);
			}
			else {
				printf("Not found !\n");
			}
			break;
			
		}

	}  while (choose !=5);
	return 0;
}

void display_bt(BTA* rootDic){
	/* must fix for dictionary output */
	int val; //rsize
	long j = 0;
	char word[MAX_LEN];
	char mean[MAX_LEN];
	btpos(rootDic, ZSTART); //ZSTART = 1;
	
	while(btseln(rootDic, word, mean, sizeof(char)*MAX_LEN, &val) == 0) {
		printf("%15s\t %15s\n",  word, mean);
		j++;	
	}
	printf("n = %ld", j);
}
