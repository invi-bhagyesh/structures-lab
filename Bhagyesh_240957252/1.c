#include <stdio.h>
#include <stdlib.h>
typedef struct Node { int data; struct Node *left, *right; } Node;

Node* insert(Node* root, int val) {
    if (!root) {
        Node *node = (Node*)malloc(sizeof(Node));
        node->data = val; node->left = node->right = NULL; return node;
    }
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}
void inorder(Node* root) { if(root){inorder(root->left); printf("%d ",root->data); inorder(root->right);} }
void preorder(Node* root) { if(root){printf("%d ",root->data); preorder(root->left); preorder(root->right);} }
void postorder(Node* root) { if(root){postorder(root->left); postorder(root->right); printf("%d ",root->data);} }

int main() {
    Node *root = NULL; int n, x;
    printf("Enter number of nodes: "); scanf("%d", &n);
    printf("Enter elements:\n");
    for (int i=0; i<n; i++) { scanf("%d",&x); root = insert(root, x); }
    printf("Inorder: "); inorder(root); printf("\n");
    printf("Preorder: "); preorder(root); printf("\n");
    printf("Postorder: "); postorder(root); printf("\n");
    return 0;
}
