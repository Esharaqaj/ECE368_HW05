#ifndef __HW05_H__
#define __HW05_H__
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int x;
    int y;
    struct Node* left;
    struct Node* right;
    int copy;
} Node;

typedef struct List {
    int x;
    int y;
    int copy;
    struct List* next;
} List;

void printList(List*);
List* createLinkNode(int, int); 
List* linkInsertion(List* root, int, int);
List* splitList(List*);
List* mergeList(List*, List*);
List* MergeSort(List*);
Node* listToBst(List*);                   // Convert sorted linked list to a balanced BST
Node* createBstNode(int ,int, int);   // Create a new BST node
void inOrderTraversal(Node*);             // Perform in-order traversal of the BST
int bstSearch(Node*, int, int, int);
bool yChecker(Node*, int,int, int);


// Node* insert_node(Node*, int);
// int getBalance(Node*);
// int height(Node*);
// int max(int, int);
// Node* rightRotate(Node*);
// Node* leftRotate(Node*);
// int getDistance(int, int, int, int);
// Node* createNode(int);
// void inorderTraversal(Node*);
// int avlSearch(Node*, int);
// void deallocate(Node*);


#endif
