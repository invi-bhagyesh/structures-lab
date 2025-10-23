#include <stdio.h>
#include <stdlib.h>
typedef struct Node { int data; struct Node *left, *right; } Node;
Node* insert(Node* root, int val) {
    if (!root) { Node *node = malloc(sizeof(Node)); node->data=val; node->left=node->right=NULL; return node; }
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}
int findmin(Node *root) { while(root&&root->left) root=root->left; return root?root->data:-1; }
int findmax(Node *root) { while(root&&root->right) root=root->right; return root?root->data:-1;}
int main() {
    Node *root=NULL; int n,x;
    printf("Enter number of nodes: "); scanf("%d",&n);
    printf("Enter elements:\n");
    for(int i=0;i<n;i++) { scanf("%d",&x); root=insert(root,x);}
    printf("Min: %d\n", findmin(root));
    printf("Max: %d\n", findmax(root));
    return 0;
}
