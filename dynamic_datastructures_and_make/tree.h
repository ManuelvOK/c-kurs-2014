#include <stdlib.h>
#include <stdio.h>

struct Node {
	int val;
	struct Node* left;
	struct Node* right;
};

struct Node* Node(int);
void insert(struct Node**, int);
void freeTree(struct Node**);
void printTree(struct Node*);
