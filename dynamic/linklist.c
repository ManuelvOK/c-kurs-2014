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
int append(struct ListElement* elem, int val) {
    if (elem->next == NULL) {
        elem->next = init(val);
        return 1;
    }
    return 0;
}

// print a list elements
void print(struct ListElement* elem) {
    printf("%d\n", elem->val);
}

// delete list element
void delete(struct ListElement* elem) {
    free(elem);
}

// iterate through list and apply f() on each list element
void mapProc(void (*f)(struct ListElement*), struct ListElement* start) {
    struct ListElement* current;
    for (current = start; current != NULL; current = current->next) {
        f(current);
    }
}

void mapFunc(int (*f)(struct ListElement*, int), struct ListElement* start, int value) {
    struct ListElement* current;
    for (current = start; current != NULL; current = current->next) {
        if (f(current, value))
            return;
    }
}

int main(int argc, const char *argv[]) {
    struct ListElement* head = init(42);
    mapFunc(append, head, 23);
    mapProc(print, head);
    mapProc(delete, head);
    /*
     * Run the program for multiple times and see what happens here.
     * Do you know why?
     */
    mapProc(print, head);
    return 0;
}
