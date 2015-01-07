#include <stdlib.h>

struct listElement{
	int val;
	struct listElement* next;
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

void freeAll(struct listElement* head) {
	// löscht alle Elemente einer Liste
}

void printList(struct listElement* head) {
	//printet jedes einzelne listenelement
}

//euch ist langweilig?
void prepend(struct listElement** head, int val) {
	// füge eine neues Element an den Anfang ein
}

int main(){
	struct listElement* head = (struct listElement*) calloc(1, sizeof(struct listElement));
	head->val = 1;
	head->next = NULL;
	// now add stuff
	append(head, 2);
	append(head, 3);
	append(head, 4);
	freeAll(head);

}
