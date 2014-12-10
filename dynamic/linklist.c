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
void append(struct ListElement* start, int value) {
    struct ListElement* current;
    if (start == NULL)
        return;
    for (current = start; current->next != NULL; current = current->next);
    current->next = init(value);
}

// create an integer sequence from first to last
struct ListElement* sequence(int first, int last) {
    struct ListElement* current;
    for (current = init(first++); first <= last; first++)
        append(current, first); //  why is this inefficient?
    return current;
}

// delete all list elements beginning from start
void delete(struct ListElement* start) {
    struct ListElement* current;
    for (current = start; current != NULL; current = current->next)
        free(current);
}


// print a list elements
void print(struct ListElement* elem) {
    static int index = 0;
    if (index == 0)
        printf("[");
    printf("%d", elem->value);
    if (elem->next != NULL) {
        printf(", ");
        index++;
    }
    else {
        printf("]\n");
        index = 0;
    }
}

void incr(struct ListElement* elem) {
    elem->value++;
}

int mult(int a, int b) {
    return a * b;
}

int add(int a, int b) {
    return a + b;
}

int isZero(struct ListElement* current) {
	return current->value == 0;
}

// iterate through list and delete all elements
// if f() returns true (1)
void filter(int (*f)(struct ListElement*),
		struct ListElement** head) {
	struct ListElement* current;
	while (f(*head)) {
		struct ListElement* toDelete = *head;
		*head = (*head)->next;
		free(toDelete);
	}

	for (current = *head; current != 0; current = current->next) {
		while (current->next && f(current->next)) {
			struct ListElement* toDelete = current->next;
			current->next = current->next->next;
			free(toDelete);
		}
	}
}


void cutOut(struct ListElement* start, int i){
	struct ListElement* current;
	for (current = start; i > 2; i--) {
		if (current->next == NULL)
			return;
		current = current->next;
	}
	struct ListElement* toDelete = current->next;
	current->next = current->next->next;
	free(toDelete);
}

// iterate through list and apply f() on each list element
void map(void (*f)(struct ListElement*), struct ListElement* start) {
    struct ListElement* current;
    for (current = start; current != NULL; current = current->next) {
        f(current);
    }
}

// iterate through list and apply f() on each list element,
// the parameters being value and the last result of f()
int fold(int (*f)(int, int), struct ListElement* start, int value) {
    struct ListElement* current;
    for (current = start; current != NULL; current = current->next) {
        value = f(current->value, value);
    }
    return value;
}

int inputListLength() {
    int n;
    puts("Create sequence from 1 to ?");
    scanf("%d", &n);
    return n;
}

int main(int argc, const char *argv[]) {
    int n = inputListLength();
    struct ListElement* head = sequence(1, n);
	append(head, 0);
	append(head, 0);
	append(head, 0);
	append(head, 0);
    map(print, head);
	//cutOut(head, 5);
	filter(isZero, &head);
	map(print, head);
    //printf("Factorial of %d: %d\n", n, fold(mult, head, 1));
    //printf("Sum of 1,...,%d: %d\n", n, fold(add, head, 0));
    delete(head);
    return 0;
}
