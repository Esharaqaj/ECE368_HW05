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

    int r_x, r_y, r_radi;
    int x, y;
    Node* bst_root = NULL;
    List* l_root = NULL;

    while(fscanf(file,"%d %d", &x, &y) == 2)
    {
        l_root = linkInsertion(l_root, x, y);
    }
    // printList(l_root);

    l_root = MergeSort(l_root);
    //printList(l_root);

    bst_root = listToBst(l_root);
    // inOrderTraversal(bst_root);

    while(scanf("%d %d %d", &r_x, &r_y, &r_radi) == 3)
    {
        int dist = bstSearch(bst_root, r_x, r_y, r_radi);
        printf("%d\n", dist);
    }

    deallocate(bst_root);
    fclose(file);
    return EXIT_SUCCESS;
}

List* createLinkNode(int x, int y)
{
    List* new_node = malloc(sizeof(List));
    new_node->x = x;
    new_node->y = y;
    new_node->copy = 1;
    new_node->next = NULL;
    return(new_node);
}

List* linkInsertion(List* root, int x, int y)
{
    if(root == NULL)
    {
        root = createLinkNode(x, y);
        return(root);
    }

    List* cur = root;
    while(cur->next != NULL) cur = cur->next;

    cur->next = linkInsertion(cur->next,x, y);
    return(root);
}

void printList(List* head) {
    List* current = head; // Start from the head of the list
    while (current != NULL) { // Traverse until the end of the list
        printf("x: %d, y: %d\n", current->x, current->y);
        current = current->next; // Move to the next node
    }
}

List* splitList(List* root)
{
    List* fast = root;
    List* slow = root;

    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        if(fast != NULL)
        {
            slow = slow->next;
        }
    }

    List* temp = slow->next;
    slow->next = NULL;
    return (temp);

}

List* mergeList(List* first, List* second)
{
    if(first == NULL) return second;
    if(second == NULL) return first;

    if(first->x < second->x)
    {
        first->next = mergeList(first->next,second);
        return first;

    } 
    else if(first->x > second->x)
    {
        second->next = mergeList(first,second->next);
        return second;
    }
    else
    {
        if(first->y < second->y)
        {
        first->next = mergeList(first->next,second);
        return first;
        }
        else if(first->y > second->y)
        {
        second->next = mergeList(first,second->next);
        return second;
        }
        else
        {
            first->copy += 1;
            first->next = mergeList(first, second->next);
            return first;
        }
    }
}

List* MergeSort(List* head) 
{
  
    // Base case: if the list is empty or has only one node, 
    // it's already sorted
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves
    List* second = splitList(head);

    // Recursively sort each half
    head = MergeSort(head);
    second = MergeSort(second);

    // Merge the two sorted halves
    return mergeList(head, second);
}


Node* listToBst(List* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->next == NULL) {

        Node* temp = createBstNode(root->x, root->y, root->copy);
        free(root);
        return temp;
    }

    List* mid = splitList(root);
    
    Node* bstRoot = createBstNode(mid->x, mid->y, mid->copy);
    bstRoot->left = listToBst(root);
    bstRoot->right = listToBst(mid->next);

    free(mid);

    return bstRoot;
}

Node* createBstNode(int x, int y, int copy)
{
    Node* root = malloc(sizeof(Node));
    root->x = x;
    root->y = y;
    root->copy = copy;
    root->left = NULL;
    root->right = NULL;

    return(root);
}

void inOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    // Visit left subtree
    inOrderTraversal(root->left);

    // Visit root
    printf("Bst x:%d and y:%d \n", root->x, root->y);

    // Visit right subtree
    inOrderTraversal(root->right);
}

int bstSearch(Node* root, int x, int y, int radius)
{

    if(root == NULL) return 0;
    int dist = 0; 
 
    if(((root->x == x) && (yChecker(root,x, y,radius))) || (((root->x <= radius+x ) && (root->x >= x - radius)) && (yChecker(root,x, y,radius))))
    {
        dist += root->copy;
        dist+= bstSearch(root->left, x, y, radius);
        dist+= bstSearch(root->right, x, y, radius);
        return dist;
    }

    else if(root->x > radius+x)
    {
        dist += bstSearch(root->left, x, y, radius);
        return dist;
    } 
       
    else if(root->x < x - radius)
    {
        dist += bstSearch(root->right, x, y, radius);
        return dist;
    }

    else 
    {
        dist += bstSearch(root->left, x, y, radius);
        dist += bstSearch(root->right, x, y, radius);

        return dist;
    }

return dist;
    
}


bool yChecker(Node* root, int r_x, int r_y, int radius)
{
    int x = root->x;
    int y = root->y;
    int distSquared = (x - r_x) * (x - r_x) + (y - r_y) * (y - r_y); // Calculate squared distance
    int radiusSquared = radius * radius; // Calculate squared radius
    return (distSquared <= radiusSquared); // Compare squared values
}

void deallocate(Node* root)
{
    if(root == NULL) return;

    deallocate(root->left);
    deallocate(root->right);

    free(root);
}
