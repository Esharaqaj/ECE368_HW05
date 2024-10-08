#ifndef __HW05_H__
#define __HW05_H__
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
    int height;
    int copy;
}Node;

Node* insert_node(Node*, int);
int getBalance(Node*);
int height(Node*);
int max(int, int);
Node* rightRotate(Node*);
Node* leftRotate(Node*);
int getDistance(int, int, int, int);
Node* createNode(int);
void inorderTraversal(Node*);
int avlSearch(Node*, int);
void deallocate(Node*);


#endif