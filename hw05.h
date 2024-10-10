#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct point {
    int x, y;
} Point;

typedef struct tNode {
    Point point;
    struct tNode *left;
    struct tNode *right;
    int height;
} TNode;

// Function prototypes
int height(TNode* node);
int getBalance(TNode* node);
int max(int a, int b);
int isInCircle(Point p, int h, int k, int r);
void search(TNode* node, int h, int k, int r, int* count);
void freeTree(TNode* node);