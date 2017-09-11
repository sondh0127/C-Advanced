#include <string.h>
#include <ctype.h>

#ifndef MAX_STR_LEN
#define MAX_STR_LEN 2000
#endif

void strTrim(char *s); // Xoá hết ký tự trắng bị đúp, xoá kí tự trắng ở đầu, cuối, thay hết kí tự trắng thành dấu cách
void strLowerCase(char *p);
void strUpperCase(char *p);

// Cắt xâu thành nhiều xâu nhỏ theo dấu cách
void strSplit(char* s, char arr[][MAX_STR_LEN], int * n); // n is number of words

// Nối các xâu từ begin đến end trong mảng arr thành xâu s bằng kí tự delim
void strJoin(char *s, char arr[][MAX_STR_LEN], int begin, int end, const char * delim);

// So sánh tên. Các tên được cắt ra thành 3 phần và loại bỏ các dấu cách thừa
// So sánh tên > tên đệm > họ
int nameCompare(char* fullname1, char* fullname2);

void strLowerCase(char *p) {
	for ( ; *p; ++p) *p = tolower(*p);
}

void strUpperCase(char *p) {
	for ( ; *p; ++p) *p = toupper(*p);
}


// - remove space at last and at the begin
// - remove duplicated spaces
// - turn all space into #32 ASCII
void strTrim(char *s) {
	int spaceBefore;
	int ptr1; // pointer 1: writing pointer;
	int ptr2; // reading pointer;

	spaceBefore = 1;
	ptr2 = 0; ptr1 = -1;
	while (ptr2 < strlen(s)) {
		if (isspace(s[ptr2])) {
			if (!spaceBefore){
				s[++ptr1] = ' ';
				spaceBefore = 1;
			} 
		} else {
			s[++ptr1] = s[ptr2];
			spaceBefore = 0;
		}
		ptr2++;
	}

	if (ptr1 == -1) {
		s[0] = '\0';
	}

	// remove last space
	if (isspace(s[ptr1])) {
		s[ptr1] = '\0';
	} else {
		s[ptr1+1] = '\0';
	}

}


// Split a string using space as delim
void strSplit(char* s, char arr[][MAX_STR_LEN], int * n) { // n is number of words
	char tmp[MAX_STR_LEN];
	char * word;

	strcpy(tmp, s);
	strTrim(tmp);

	*n = 0;
	word = strtok(tmp, " ");
	while (word != NULL) {
		strcpy(arr[*n], word);
		(*n)++;
		word = strtok(NULL, " ");
	}
}

// Join a string using optional delim
void strJoin(char *s, char arr[][MAX_STR_LEN], int begin, int end, const char * delim) {
	// empty string s;
	s[0] = '\0';

	int i;
	for (i = begin; i <= end; ++i){
		if (strlen(s) != 0) {
			strcat(s, delim);
		}
		strcat(s, arr[i]);
	}
}


// return 0: the same; <0: name1 < name2; >0: name1 > name2
int nameCompare(char* fullname1, char* fullname2) {
	char familyName1[MAX_STR_LEN]; strcpy(familyName1, "");
	char surname1[MAX_STR_LEN]; strcpy(surname1, "");
	char name1[MAX_STR_LEN]; strcpy(name1, "");
	char familyName2[MAX_STR_LEN]; strcpy(familyName2, "");
	char surname2[MAX_STR_LEN]; strcpy(surname2, "");
	char name2[MAX_STR_LEN]; strcpy(name2, "");

	char a[100][MAX_STR_LEN]; int n;

	strSplit(fullname1, a, &n);
	if (n > 0) {
		strcpy(name1, a[n-1]);
	}
	if (n > 1) {
		strcpy(familyName1, a[0]);
	}
	if (n > 2) {
		strJoin(surname1, a, 1, n-2, " ");
	}

	strSplit(fullname2, a, &n);
	if (n > 0) {
		strcpy(name2, a[n-1]);
	}
	if (n > 1) {
		strcpy(familyName2, a[0]);
	}
	if (n > 2) {
		strJoin(surname2, a, 1, n-2, " ");
	}

	strLowerCase(familyName1); strLowerCase(surname1); strLowerCase(name1); 
	strLowerCase(familyName2); strLowerCase(surname2); strLowerCase(name2); 

	if (strcmp(name1, name2) != 0) {
		return strcmp(name1, name2);
	} else {
		if (strcmp(surname1, surname2) != 0) {
			return strcmp(surname1, surname2);
		} else {
			return strcmp(familyName1, familyName2);
		}
	}

	return 0;
}

