#include <stdio.h>
#include <stdlib.h>
typedef struct Node { int data; struct Node *left, *right; } Node;
Node* insert(Node* root, int val) {
    if (!root) { Node *node = malloc(sizeof(Node)); node->data=val; node->left=node->right=NULL; return node; }
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}
Node* minValueNode(Node *n) { while (n && n->left) n=n->left; return n; }
Node* delete(Node* root,int key) {
    if(!root) return root;
    if(key<root->data) root->left=delete(root->left,key);
    else if(key>root->data) root->right=delete(root->right,key);
    else {
        if(!root->left) { Node *r=root->right; free(root); return r; }
        if(!root->right) { Node *l=root->left; free(root); return l; }
        Node*t=minValueNode(root->right); root->data=t->data;
        root->right=delete(root->right,t->data);
    }
    return root;
}
void inorder(Node* root) { if(root){inorder(root->left); printf("%d ",root->data); inorder(root->right);} }
int main() {
    Node *root=NULL; int n,x;
    printf("Enter number of nodes: "); scanf("%d",&n);
    printf("Enter elements:\n");
    for(int i=0;i<n;i++) { scanf("%d",&x); root=insert(root,x);}
    printf("Enter value to delete: "); scanf("%d",&x);
    root=delete(root,x);
    printf("Inorder after delete: "); inorder(root); printf("\n");
    return 0;
}
// 5
// 40 20 60 10 30
// 20
// Inorder after delete: 10 30 40 60 
