#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"
#include "string_ext.h"
#include "extio.h"

int main()
{
	FILE *fp;
	if ((fp = fopen("phonebook.txt","r")) == NULL){
		printf("Error! opening file");
		// Program exits if the file pointer returns NULL.
		exit(1);
	}
	int ch, size = 0;
	while((ch = fgetc(fp))!= EOF) {
		if(ch == '\n')
			size++;
	}
	printf("Size of file: %d Phone\n", size);
	fseek(fp, 0,SEEK_SET);
	Phone arr[size];
	int i = 0;
	while(!feof(fp)) {
		fscanf(fp, "%70[^\t]\t%20[^\n]\n", arr[i].name, arr[i].phone);
		//printf("%s|\t%s\n",arr[i].name, arr[i].phone);
		i++;
	}
	
	qsort(arr, size, sizeof(Phone), comparator);

	for(int i = 0; i < size; i++) {
		printf("%25s|\t%20s\n",arr[i].name, arr[i].phone);
	}

	fclose(fp);
    return 0;
}
