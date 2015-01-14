#include <stdlib.h>
#include <stdio.h>

struct listElement{
	int val;
	struct listElement* next;
	struct listElement* prev;
};

void append(struct listElement* head, int val){
	// hängt an das Ende der Liste, die mit head beginnt,
	// ein Listelement mit dem Wert val an.
	struct listElement* current = head;
	while (current->next != NULL){
		current = current->next;
	}

	struct listElement* toAppend;
	toAppend = (struct listElement*) calloc(1, sizeof(struct listElement));
	toAppend->val = val;
	toAppend->next = NULL;

	current->next = toAppend;


}

void freeAll(struct listElement** head) {
	// löscht alle Elemente einer Liste
	if((*head)->next == NULL){
		free(*head);
		return;
	}
	freeAll(&(*head)->next);
	free(*head);
	*head = NULL;
}

void printList(struct listElement* head) {
	//printet jedes einzelne listenelement
	if(head != NULL){
		printf("%d\t", head->val);
		printList(head->next);
	}
	else
		printf("\n");
}

//euch ist langweilig?
void prepend(struct listElement** pToHead, int val) {
	// füge eine neues Element an den Anfang ein
	struct listElement* toPrepend;
	toPrepend = (struct listElement*) calloc(1, sizeof(struct listElement));
	toPrepend->val = val;
	toPrepend->next = *pToHead;
	*pToHead = toPrepend;
}

void deleteElem(struct listElement* head, int index){
	//löscht das element mit index index aus der doppelt verketteten Liste head
	//langweilig? Dann mach's mit nem Doppelpointer.
}

int main(){
	struct listElement* head = (struct listElement*) calloc(1, sizeof(struct listElement));
	head->val = 1;
	head->next = NULL;
	// now add stuff
	append(head, 2);
	append(head, 3);
	append(head, 4);
	printList(head);
	prepend(&head, 0);
	printList(head);
	freeAll(&head);
	printList(head);

}
