#include "tree.h"


struct Node* Node(int val) {
    struct Node* newNode =
        (struct Node*) calloc(1, sizeof(struct Node));
    if (newNode == NULL)
        exit(EXIT_FAILURE);
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(struct Node** root, int val) {
    if (*root == NULL)
        *root = Node(val);
    else {
        if (val < (*root)->val)
            insert(&(*root)->left, val);
        else if (val > (*root)->val)
            insert(&(*root)->right, val);
        else
            return;
    }
}

void freeTree(struct Node** root) {
    if (*root == NULL)
        return;
    freeTree(&(*root)->left);
    freeTree(&(*root)->right);
    free(*root);
    *root = NULL;
}

void printTree(struct Node* root) {
    if (root == NULL)
        return;
    printTree(root->left);
    printf("%d\n", root->val);
    printTree(root->right);
}
