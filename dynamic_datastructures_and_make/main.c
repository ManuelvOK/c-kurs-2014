#include "linklist2.h"
#include "tree.h"

int main(int argc, char *argv[]) {
    /* Test the list implementation */
    struct ListElement* head = ListElement(0);
    append(head, 1);
    append(head, 2);
    append(head, 3);
    printList(head);
    deleteElem(&head, 2);
    puts("Aus der Mitte gelöscht:");
    printList(head);
    deleteElem(&head, 0);
    puts("Vom Anfang gelöscht:");
    printList(head);
    deleteElem(&head, 1);
    puts("Vom Ende gelöscht:");
    printList(head);
    freeAll(&head);
    /* Test the tree implementation */
    struct Node* root = Node(24);
    insert(&root, 23);
    insert(&root, 31);
    insert(&root, 19);
    insert(&root, 3);
    insert(&root, 84);
    insert(&root, 46);
    insert(&root, 12);
    printTree(root);
    freeTree(&root);
    return 0;
}
