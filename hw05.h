#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct values {
    int x, y;
} Values;

typedef struct Node {
    Values Values;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Function prototypes
int height(Node* node);
int getBalance(Node* node);
int max(int a, int b);
int radiusChecker(Values p, int h, int k, int r);
void search(Node* node, int h, int k, int r, int* count);
void freeTree(Node* node);
