#include <stdlib.h>
#include <stdio.h>

struct ListElement {
	int val;
	struct ListElement* next;
	struct ListElement* prev;
};

struct ListElement* ListElement(int);
void append(struct ListElement*, int);
void freeAll(struct ListElement**);
void printList(struct ListElement*);
void prepend(struct ListElement**, int);
void deleteElem(struct ListElement**, int);
