#include "hw05.h"

// Helper function to construct a new node
Node *createNode(Values Values){
    Node *node = malloc(sizeof(Node));
    node->Values = Values;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right rotation
Node* rotateRight(Node* root) {
    Node* newRoot = root->left;
    Node* temp = root->right;
    newRoot->right = root;
    root->left = temp;

    // Update heights
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

// Left rotation
Node* rotateLeft(Node* root) {
    Node* newRoot = root->right;
    Node* temp = newRoot->left;
    newRoot->left = root;
    root->right = temp;

    // Update heights
    root->height = max(height(root->left), height(root->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}


int radiusChecker(Values p, int r_x, int r_y, int r) {
    int x = p.x - r_x;
    int y = p.y - r_y;
    return ((x * x) + (y * y)) <= r * r;
}

void search(Node* node, int r_x, int r_y, int r, int* count) {
    if (node == NULL)
        return;

    if (radiusChecker(node->Values, r_x, r_y, r)) {
        (*count)++;
    }

    if (r_x - r <= node->Values.x)
        search(node->left, r_x, r_y, r, count);

    if (r_x + r >= node->Values.x)
        search(node->right, r_x, r_y, r, count);
}

void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    Node* root = NULL;
    int x, y;

    while (fscanf(file, "%d %d", &x, &y) != EOF) {
        Values Values = {x, y};
        root = insert(root, Values);
    }
    fclose(file);

    int h, k, r;
    while (scanf("%d %d %d", &h, &k, &r) != EOF) {
        int count = 0;
        search(root, h, k, r, &count);
        printf("%d\n", count);
    }

    freeTree(root);

    return 0;
}

Node* insert(Node* node, Values point) {
    if (node == NULL)
        return constructNode(point);

    if (point.x < node->point.x || (point.x == node->point.x && point.y < node->point.y)) {
        node->left = insert(node->left, point);
    } else if (point.x > node->point.x || (point.x == node->point.x && point.y > node->point.y)) {
        node->right = insert(node->right, point);
    } else {
        return node; // Point already exists, no insertion
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && (point.x < node->left->point.x || (point.x == node->left->point.x && point.y < node->left->point.y))) {
        return rotateRight(node);
    }
    // Right Right Case
    if (balance < -1 && (point.x > node->right->point.x || (point.x == node->right->point.x && point.y > node->right->point.y))) {
        return rotateLeft(node);
    }
    // Left Right Case
    if (balance > 1 && (point.x > node->left->point.x || (point.x == node->left->point.x && point.y > node->left->point.y))) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Right Left Case
    if (balance < -1 && (point.x < node->right->point.x || (point.x == node->right->point.x && point.y < node->right->point.y))) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
