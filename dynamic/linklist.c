#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    int value;
    struct ListElement* next;
};

// allocate memory for a new element
struct ListElement* init(int value) {
    struct ListElement* new =
        (struct ListElement*) malloc(sizeof(struct ListElement));
    new->value = value;
    new->next = NULL;
    return new;
}

// add new element at the end of the list
int append(struct ListElement* elem, int value) {
    if (elem->next == NULL) {
        elem->next = init(value);
        return 1;
    }
    return 0;
}

// return the value of the i-th list element
int get(struct ListElement* elem, int index) {
    static int position = 0;
    if (position == index) {
        position = 0;
        return elem->value;
    }
    else {
        position++;
        return 0;
    }
}

// print a list elements
void print(struct ListElement* elem) {
    printf("%d\n", elem->value);
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

int mapFunc(int (*f)(struct ListElement*, int), struct ListElement* start, int value) {
    struct ListElement* current;
    for (current = start; current != NULL; current = current->next) {
        int result = f(current, value);
        if (result)
            return result;
    }
    return 0;
}

int main(int argc, const char *argv[]) {
    struct ListElement* head = init(42);
    mapFunc(append, head, 23);
    mapProc(print, head);
    printf("2nd element: %d\n", mapFunc(get, head, 1));
    mapProc(delete, head);
    /*
     * Run the program for multiple times and see what happens here.
     * Do you know why?
     */
    mapProc(print, head);
    return 0;
}
