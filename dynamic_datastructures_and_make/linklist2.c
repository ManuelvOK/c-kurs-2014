#include "linklist2.h"

// erstelle ein neues Listenelement
struct ListElement* ListElement(int val) {
    struct ListElement* newElem =
        (struct ListElement*) calloc(1, sizeof(struct ListElement));
    if (newElem == NULL)
        exit(EXIT_FAILURE);
    newElem->val = val;
    newElem->prev = NULL;
    newElem->next = NULL;
    return newElem;
}

// hängt an das Ende der Liste, die mit head beginnt, ein Listelement mit
// dem Wert val an.
void append(struct ListElement* head, int val) {
	struct ListElement* current = head;
	while (current->next != NULL)
		current = current->next;

	struct ListElement* toAppend = ListElement(val);
    toAppend->prev = current;
	current->next = toAppend;
}

// löscht alle Elemente einer Liste
void freeAll(struct ListElement** head) {
	if ((*head)->next == NULL) {
		free(*head);
		return;
	}
	freeAll(&(*head)->next);
	free(*head);
	*head = NULL;
}

// printet jedes einzelne listenelement
void printList(struct ListElement* head) {
    printf("[");
    if (head != NULL) {
        printf("%d", head->val);
        head = head->next;
    }
    for (; head != NULL; head = head->next)
		printf(", %d", head->val);
	printf("]\n");
}

// füge eine neues Element an den Anfang ein
void prepend(struct ListElement** pToHead, int val) {
	struct ListElement* toPrepend = ListElement(val);
    toPrepend->next = *pToHead;
	*pToHead = toPrepend;
}

// löscht das element mit index index aus der doppelt verketteten Liste head
void deleteElem(struct ListElement** head, int index) {
    struct ListElement* current;
    for (current = *head;
        current != NULL && index > 0;
        current = current->next, index--);
    if (current == NULL)
        return;
    if ((current)->next != NULL)
        (current)->next->prev = (current)->prev;
    if ((current)->prev != NULL)
        (current)->prev->next = (current)->next;
    else
        *head = current->next;
    free(current);
}
