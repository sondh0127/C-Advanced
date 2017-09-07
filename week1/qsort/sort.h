#ifndef _SORT_H
#define _SORT_H_
typedef struct Phone {
	char name[70];
	char phone[20];
}Phone;

int comparator(const void* p, const void *q);
#endif
// _SORT_H
