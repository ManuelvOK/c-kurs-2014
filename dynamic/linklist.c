#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    int val;
    struct ListElement* next;
};

// allocate memory for a new element
struct ListElement* init(int val) {
    struct ListElement* new =
        (struct ListElement*) malloc(sizeof(struct ListElement));
    new->val = val;
    new->next = NULL;
    return new;
}

// add new element at the end of the list
void append(struct ListElement* current, int val) {
    if (current == NULL)
        return;
    for (; current->next != NULL; current = current->next);
    current->next = init(val);
}

// print all ListElements
void printList(struct ListElement* current) {
    for (; current != NULL; current = current->next)
        printf("%d\n", current->val);
}

int main(int argc, const char *argv[]) {
    struct ListElement* head = init(42);
    append(head, 23);
    printList(head);
    return 0;
}
