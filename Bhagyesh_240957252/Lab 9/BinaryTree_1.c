#include <stdio.h>
#include <stdlib.h>

// Define a structure for tree nodes
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack structure for iterative traversals
#define MAX 100
typedef struct Stack {
    Node* data[MAX];
    int top;
} Stack;

void initStack(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, Node* node) { s->data[++(s->top)] = node; }
Node* pop(Stack* s) { return s->data[(s->top)--]; }
Node* peek(Stack* s) { return s->data[s->top]; }

// Queue structure for BFS operations (parent, depth)
typedef struct Queue {
    Node* data[MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) { q->front = q->rear = -1; }
int isQEmpty(Queue* q) { return q->front == q->rear; }
void enqueue(Queue* q, Node* node) { q->data[++(q->rear)] = node; }
Node* dequeue(Queue* q) { return q->data[++(q->front)]; }

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert node in binary tree (level order for balanced structure)
void insert(Node** root, int data) {
    Node* newNode = createNode(data);
    if (!*root) { *root = newNode; return; }
    Queue q; initQueue(&q);
    enqueue(&q, *root);
    while (!isQEmpty(&q)) {
        Node* temp = dequeue(&q);
        if (!temp->left) { temp->left = newNode; return; }
        else enqueue(&q, temp->left);
        if (!temp->right) { temp->right = newNode; return; }
        else enqueue(&q, temp->right);
    }
}

// 1. Iterative Inorder Traversal
void inorderIterative(Node* root) {
    Stack s; initStack(&s);
    Node* curr = root;
    while (curr || !isEmpty(&s)) {
        while (curr) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    printf("\n");
}

// 2. Iterative Postorder Traversal
void postorderIterative(Node* root) {
    Stack s1, s2;
    initStack(&s1); initStack(&s2);
    if (root) push(&s1, root);
    while (!isEmpty(&s1)) {
        Node* curr = pop(&s1);
        push(&s2, curr);
        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }
    while (!isEmpty(&s2)) {
        printf("%d ", pop(&s2)->data);
    }
    printf("\n");
}

// 3. Iterative Preorder Traversal
void preorderIterative(Node* root) {
    Stack s; initStack(&s);
    if (root) push(&s, root);
    while (!isEmpty(&s)) {
        Node* curr = pop(&s);
        printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
    printf("\n");
}

// 4. Print Parent of a Given Element
void printParent(Node* root, int key) {
    if (!root || root->data == key) {
        printf("No parent (root or not found)\n");
        return;
    }
    Queue q; initQueue(&q);
    enqueue(&q, root);
    while (!isQEmpty(&q)) {
        Node* curr = dequeue(&q);
        if (curr->left && curr->left->data == key) {
            printf("Parent of %d is %d\n", key, curr->data);
            return;
        }
        if (curr->right && curr->right->data == key) {
            printf("Parent of %d is %d\n", key, curr->data);
            return;
        }
        if (curr->left) enqueue(&q, curr->left);
        if (curr->right) enqueue(&q, curr->right);
    }
    printf("Element %d not found (or is root)\n", key);
}

// 5. Print Depth (Height) of the Tree (level order)
int treeDepth(Node* root) {
    if (!root) return 0;
    Queue q; initQueue(&q);
    enqueue(&q, root);
    int height = 0;
    while (1) {
        int nodeCount = q.rear - q.front;
        if (nodeCount == 0)
            break;
        height++;
        while (nodeCount > 0) {
            Node* node = dequeue(&q);
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
            nodeCount--;
        }
    }
    return height;
}

// 6. Print Ancestors of a Given Element (iterative backtracking)
void printAncestors(Node* root, int key) {
    Stack s; initStack(&s);
    Node* curr = root;
    Node* prev = NULL;
    while (1) {
        while (curr && curr->data != key) {
            push(&s, curr);
            curr = curr->left;
        }
        if (curr && curr->data == key) break;
        if (isEmpty(&s)) {
            printf("Element %d not found\n", key);
            return;
        }
        curr = peek(&s);
        if (!curr->right || curr->right == prev) {
            prev = pop(&s);
            curr = NULL;
        } else {
            curr = curr->right;
        }
    }
    printf("Ancestors of %d: ", key);
    for (int i = 0; i <= s.top; i++)
        printf("%d ", s.data[i]->data);
    printf("\n");
}

// 7. Count Number of Leaf Nodes (iterative)
int countLeafNodes(Node* root) {
    if (!root) return 0;
    Stack s; initStack(&s); int count = 0;
    push(&s, root);
    while (!isEmpty(&s)) {
        Node* curr = pop(&s);
        if (!curr->left && !curr->right)
            count++;
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
    return count;
}

// Example usage
int main() {
    Node* root = NULL;
    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
    insert(&root, 4);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 7);

    printf("Inorder: ");   inorderIterative(root);
    printf("Postorder: "); postorderIterative(root);
    printf("Preorder: ");  preorderIterative(root);

    printParent(root, 5);
    printParent(root, 1);

    printf("Tree height: %d\n", treeDepth(root));

    printAncestors(root, 7);
    printAncestors(root, 1);

    printf("Number of leaf nodes: %d\n", countLeafNodes(root));

    return 0;
}
