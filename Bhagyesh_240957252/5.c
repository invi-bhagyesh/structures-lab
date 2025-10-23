#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data, height;
    struct Node *left, *right;
} Node;

int max(int a, int b) { return a > b ? a : b; }

int getHeight(Node *n) { return n ? n->height : 0; }

Node *newNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

// Left rotate
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int getBalance(Node *n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

Node* insert(Node* node, int key) {
    if (!node) return newNode(key);
    if (key < node->data) node->left = insert(node->left, key);
    else if (key > node->data) node->right = insert(node->right, key);
    else return node;  // no duplicates

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);
    // RR
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);
    // LR
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void inorder(Node *root) {
    if(root) { inorder(root->left); printf("%d ", root->data); inorder(root->right);}
}

int main() {
    Node *root = NULL; int n, x;
    printf("Enter number of nodes: "); scanf("%d", &n);
    printf("Enter elements:\n");
    for(int i=0; i<n; i++) {
        scanf("%d", &x);
        root = insert(root, x);
        printf("Inorder after inserting %d: ", x);
        inorder(root);
        printf("\n");
    }
    return 0;
}


// Enter number of nodes: 6
// Enter elements:
// 30 40 50 20 10 25
// Inorder after inserting 30: 30 
// Inorder after inserting 40: 30 40 
// Inorder after inserting 50: 30 40 50 
// Inorder after inserting 20: 20 30 40 50 
// Inorder after inserting 10: 10 20 30 40 50 
// Inorder after inserting 25: 10 20 25 30 40 50 
