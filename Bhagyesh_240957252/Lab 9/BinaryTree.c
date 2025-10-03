#include <stdio.h>
#include <stdlib.h>

// Node definition
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Recursive function to create a binary tree (preorder, using -1 as NULL marker)
Node* createTree() {
    int value;
    printf("Enter node value (-1 for NULL): ");
    scanf("%d", &value);
    if (value == -1)
        return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    printf("Enter left child of %d:\n", value);
    node->left = createTree();
    printf("Enter right child of %d:\n", value);
    node->right = createTree();
    return node;
}

// Find height to help with level-order printing
int height(Node* root) {
    if (!root)
        return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

// Print nodes at a given level
void printLevel(Node* root, int level) {
    if (!root)
        return;
    if (level == 1) {
        printf("%d ", root->data);
    } else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Print tree in level order using recursion
void printLevelOrder(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
    }
    printf("\n");
}

// Example usage
int main() {
    Node* root = NULL;
    printf("Create the binary tree:\n");
    root = createTree();
    printf("Level order traversal:\n");
    printLevelOrder(root);
    return 0;
}
