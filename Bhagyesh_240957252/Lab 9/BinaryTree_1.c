#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Recursive create, used for input-driven construction
Node* create() {
    int x;
    scanf("%d", &x);
    if (x == -1) return NULL;
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = x;
    node->left = create();   // left child
    node->right = create();  // right child
    return node;
}

// Iterative traversals and utilities, as before
void inorder_iter(Node *root) {
    Node *stack[100]; int top = -1; Node *curr = root;
    while (curr || top != -1) {
        while (curr) stack[++top] = curr, curr = curr->left;
        curr = stack[top--];
        printf("%d ", curr->data);
        curr = curr->right;
    }
}
void preorder_iter(Node *root) {
    Node *stack[100]; int top = -1; if (root) stack[++top] = root;
    while (top != -1) {
        Node *curr = stack[top--]; printf("%d ", curr->data);
        if (curr->right) stack[++top] = curr->right;
        if (curr->left) stack[++top] = curr->left;
    }
}
void postorder_iter(Node *root) {
    Node *stack1[100], *stack2[100]; int top1 = -1, top2 = -1;
    if (root) stack1[++top1] = root;
    while (top1 != -1) {
        Node *curr = stack1[top1--];
        stack2[++top2] = curr;
        if (curr->left) stack1[++top1] = curr->left;
        if (curr->right) stack1[++top1] = curr->right;
    }
    while (top2 != -1) printf("%d ", stack2[top2--]->data);
}
void print_parent(Node *root, int key) {
    if (!root) return;
    if ((root->left && root->left->data == key) || (root->right && root->right->data == key))
        printf("%d\n", root->data);
    print_parent(root->left, key);
    print_parent(root->right, key);
}
int height(Node *root) {
    if (!root) return 0;
    int lh = height(root->left), rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}
int print_ancestors(Node *root, int key) {
    if (!root) return 0;
    if ((root->left && root->left->data == key) || (root->right && root->right->data == key)
       || print_ancestors(root->left, key) || print_ancestors(root->right, key)) {
        printf("%d ", root->data);
        return 1;
    }
    return 0;
}
int count_leaves(Node *root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return count_leaves(root->left) + count_leaves(root->right);
}

int main() {
    printf("Enter tree in pre-order (-1 for NULL): ");
    Node *root = create();
    printf("Inorder: "); inorder_iter(root); printf("\n");
    printf("Preorder: "); preorder_iter(root); printf("\n");
    printf("Postorder: "); postorder_iter(root); printf("\n");
    printf("Height: %d\n", height(root));
    printf("Leaf count: %d\n", count_leaves(root));
    int x;
    printf("Parent of (input): "); scanf("%d", &x); print_parent(root, x);
    printf("Ancestors of (input): "); scanf("%d", &x); print_ancestors(root, x); printf("\n");
    return 0;
}
