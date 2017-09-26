#include <stdio.h>
#include <stdlib.h>
#include "../../lib/btree/btree.h"
#include "extio.h"
#include <string.h>
#include "soundex.h"
#define MAX_LEn 100000

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
	char *filename = "test.dat";
	char *filename_Soundex = "test_soundex.dat";
	BTA *rootDic;
	BTA *soundexT;
	btinit();
	/* open file if file doesn't exist => create new file*/
	if((rootDic = btopn(filename, 0, FALSE))!= NULL) {
		printf("Open file successful!\n");
	} else {
		printf("Creating data\n");
		readFile(&rootDic, filename);
	}
	if((soundexT = btopn(filename_Soundex, 0, FALSE))!= NULL) {
		printf("Open file successful!\n");
	} else {
		printf("Creating data\n");
		///copy rootDic to soundexT for sug
		creatSoundexTree(rootDic, &soundexT);
	}
	int choose = 0;
	char word[MAX_LEn];
	char mean[MAX_LEn];
	char mean_out[MAX_LEn];
	int status, val;
	int i,k;
	char suggest[15][100];
	do {
		choose = menu();
		
		switch (choose) {
		case 5:
			// test
			;
			printf("nhap tu can goi y:\n"); readLn(stdin, word, MAX_LEn);
			
			k = suggestion(soundexT,word,suggest);
			if(k!=0)
				for(i=0;i<k;i++) printf("%s\n",suggest[i]);
			break;
		case 1:
			printf(" Input data:\n");
			printf("word:");  readLn(stdin, word, MAX_LEn);
			printf("meaning:");  readLn(stdin, mean, MAX_LEn);
			printf("%15s\t %15s\n",  word, mean);
			status = btins(rootDic, word, mean, sizeof(char)*strlen(mean));
            btsel(rootDic, word, mean_out, sizeof(char)*MAX_LEn, &val);
			printf("%15s\t %15s\n",  word, mean_out);
			break;
		case 2:
			printf(" Input data:\n");
			printf("word:");  readLn(stdin, word, MAX_LEn);
			status = bfndky(rootDic, word, &val);
			if (status != 0)
				printf("Duplicate \n");
			break;

		case 3:
			display_bt(rootDic);
			break;
		case 4:
			printf(" Input data:\n");
			printf("word:");  readLn(stdin, word, MAX_LEn);
			status = btdel(rootDic, word);
			
			//just for test 
			if(status == 0)
			{
				btsel(rootDic, word, mean_out, sizeof(char)*MAX_LEn, &val);
				printf("%15s\t %15s\n",  word, mean_out);
			}
			else {
				printf("Not found !\n");
			}
			break;
			
		}

}  while (choose != 5);
return 0;
}

void display_bt(BTA* rootDic){
	int val; //rsize
	long j = 0;
	char word[MAX_LEn];
	char mean[MAX_LEn];
	btpos(rootDic, ZSTART); //ZSTART = 1;
	
	while(btseln(rootDic, word, mean, sizeof(char)*MAX_LEn, &val) == 0) {
		printf("%15s\t %15s\n",  word, mean);
		j++;	
	}
	printf("n = %ld", j);
}
