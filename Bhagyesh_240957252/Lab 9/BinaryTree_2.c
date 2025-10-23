#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* create() {
    int x;
    scanf("%d", &x);
    if (x == -1) return NULL;
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = x;
    node->left = create(); // recursively left
    node->right = create(); // recursively right
    return node;
}

// Print level-order traversal
void print_level_order(Node *root) {
    Node* queue[100]; int f=0, r=0;
    if (!root) return;
    queue[r++] = root;
    while (f < r) {
        Node *curr = queue[f++];
        printf("%d ", curr->data);
        if (curr->left) queue[r++] = curr->left;
        if (curr->right) queue[r++] = curr->right;
    }
}

int main() {
    printf("Enter tree in pre-order (-1 for NULL): ");
    Node *root = create();
    printf("Level Order: "); print_level_order(root); printf("\n");
    return 0;
}
