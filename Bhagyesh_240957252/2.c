#include <stdio.h>
#include <stdlib.h>
typedef struct Node { int data; struct Node *left, *right; } Node;
Node* insert(Node* root, int val) {
    if (!root) { Node *node = malloc(sizeof(Node)); node->data=val; node->left=node->right=NULL; return node; }
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}
int search(Node* root, int key) {
    if (!root) return 0;
    if (root->data == key) return 1;
    return key < root->data ? search(root->left, key) : search(root->right, key);
}
int main() {
    Node *root=NULL; int n,x;
    printf("Enter number of nodes: "); scanf("%d",&n);
    printf("Enter elements:\n");
    for(int i=0;i<n;i++) { scanf("%d",&x); root=insert(root,x);}
    printf("Enter value to search: "); scanf("%d",&x);
    printf("%s\n", search(root,x) ? "Found" : "Not found");
    return 0;
}
