#include "trial.h"

// Main function to load scene and process collision queries
int main(int argc, char *argv[]) {
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

    int r_x, r_y, r_radi;
    int x, y;
    Node* bst_root = NULL;
    List* l_root = NULL;

    // Read the points from the file and build the linked list
    while (fscanf(file, "%d %d", &x, &y) == 2) {
        l_root = linkInsertion(l_root, x, y);
    }

    // Sort the list and convert it to a binary search tree (BST)
    l_root = MergeSort(l_root);
    bst_root = listToBst(l_root);

    // Handle collision queries from standard input
    while (scanf("%d %d %d", &r_x, &r_y, &r_radi) == 3) {
        int count = bstSearch(bst_root, r_x, r_y, r_radi);
        printf("%d\n", count);
    }

    // Clean up memory
    deallocate(bst_root);
    fclose(file);
    return EXIT_SUCCESS;
}

// Create a new linked list node
List* createLinkNode(int x, int y) {
    List* new_node = malloc(sizeof(List));
    new_node->x = x;
    new_node->y = y;
    new_node->copy = 1;
    new_node->next = NULL;
    return new_node;
}

// Insert a new node at the start of the linked list
List* linkInsertion(List* head, int x, int y) {
    List* newNode = createLinkNode(x, y);
    newNode->next = head;
    return newNode;
}

// Split the linked list into two halves
List* splitList(List* root) {
    if (root == NULL || root->next == NULL) return NULL;

    List* slow = root;
    List* fast = root->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    List* mid = slow->next;
    slow->next = NULL; // Split the list
    return mid;
}

// Merge two sorted linked lists
List* mergeList(List* first, List* second) {
    if (first == NULL) return second;
    if (second == NULL) return first;

    if (first->x < second->x || (first->x == second->x && first->y < second->y)) {
        first->next = mergeList(first->next, second);
        return first;
    } else if (first->x == second->x && first->y == second->y) {
        first->copy += second->copy;
        first->next = mergeList(first->next, second->next);
        free(second);
        return first;
    } else {
        second->next = mergeList(first, second->next);
        return second;
    }
}

// MergeSort implementation for linked list
List* MergeSort(List* head) {
    if (head == NULL || head->next == NULL) return head;

    List* second = splitList(head);
    head = MergeSort(head);
    second = MergeSort(second);
    return mergeList(head, second);
}

// Convert sorted linked list to BST
Node* listToBst(List* root) {
    if (root == NULL) return NULL;

    if (root->next == NULL) {
        Node* bstNode = createBstNode(root->x, root->y, root->copy);
        free(root);
        return bstNode;
    }

    List* mid = splitList(root);
    Node* bstRoot = createBstNode(mid->x, mid->y, mid->copy);

    bstRoot->left = listToBst(root);
    bstRoot->right = listToBst(mid->next);

    free(mid);
    return bstRoot;
}

// Create a new BST node
Node* createBstNode(int x, int y, int copy) {
    Node* node = malloc(sizeof(Node));
    node->x = x;
    node->y = y;
    node->copy = copy;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Search BST for points within the circle defined by (x, y, radius)
int bstSearch(Node* root, int x, int y, int radius) {
    if (root == NULL) return 0;

    int dx = root->x - x;
    int dy = root->y - y;
    int distSquared = dx * dx + dy * dy;
    int radiusSquared = radius * radius;

    int count = 0;

    // Check if the point is inside the circle
    if (distSquared <= radiusSquared) {
        count += root->copy;
    }

    // Use binary search tree properties to limit recursion
    if (root->x >= x - radius) {
        count += bstSearch(root->left, x, y, radius);
    }
    if (root->x <= x + radius) {
        count += bstSearch(root->right, x, y, radius);
    }

    return count;
}

// Free the memory used by the BST
void deallocate(Node* root) {
    if (root == NULL) return;
    deallocate(root->left);
    deallocate(root->right);
    free(root);
}
