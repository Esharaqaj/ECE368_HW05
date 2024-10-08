#include "hw05.h"

int main(int argc, char *argv[])
{
        // Check if a file is provided as an argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open the file passed as an argument
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int r_x, r_y, r_radi, x, y;
    Node* avl = NULL;

    int dist;

while(scanf("%d %d %d", &r_x, &r_y, &r_radi) == 3)
{
    fseek(file, 0, SEEK_SET);
    while(fscanf(file,"%d %d", &x, &y) == 2)
    {
        dist = getDistance(x,y,r_x,r_y);
        avl = insert_node(avl,dist);
    }

    printf("%d\n", avlSearch(avl, r_radi));
    deallocate(avl);
    avl = NULL;
    }

    fclose(file);
    return EXIT_SUCCESS;
}


Node* insert_node(Node* node, int value)
{
    if(node == NULL){
        node = createNode(value);
        return(node);
    }

    else{
        if(value < node->value){
            node->left = insert_node(node->left,value);
        }
        else if(value > node->value)
        {
            node->right = insert_node(node->right,value);
        }
        else node->copy += 1;
        return(node);
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    if (balance > 1 && value > node->left->value)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

     if (balance < -1 && value < node->right->value)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

        // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

int getDistance(int x, int y, int r_x, int r_y)
{
    return (int)sqrt(pow((x - r_x), 2) + pow((y - r_y), 2));

}

Node* createNode(int x)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = x;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    new_node->copy = 1;
    return(new_node);
}

void inorderTraversal(Node* root) {
  
    // Empty Tree
    if (root == NULL)
        return;
  
    // Recur on the left subtree
    inorderTraversal(root->left);
  
    // Visit the current node
    printf("%d\n", root->value);
  
    // Recur on the right subtree
    inorderTraversal(root->right);
}

int avlSearch(Node* root, int radius)
{
    Node* cur = root;
    if (root == NULL) {
        return 0; // No nodes found
    }

    int dists = 0;

    // Count in left subtree
    dists += avlSearch(cur->left, radius);

    // Check the current node
    if (cur->value <= radius) {
        dists += cur->copy;  // Count this node
    }

    // Count in right subtree
    dists += avlSearch(cur->right, radius);

    return dists;  // Return the accumulated count
}

void deallocate(Node* root)
{
    if(root == NULL) return;

    deallocate(root->left);
    deallocate(root->right);

    free(root);
}