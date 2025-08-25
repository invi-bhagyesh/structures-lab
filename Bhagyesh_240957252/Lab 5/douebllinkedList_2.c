#include <stdio.h>
#include <stdlib.h>

// Doubly linked list Node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Utility: Create new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert node at rear/end
void insertRear(struct Node** head, struct Node** tail, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

// Traverse list forward
void traverseForward(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Concatenate two lists: X1 + X2
void concatenate(struct Node** head1, struct Node** tail1,
                 struct Node** head2, struct Node** tail2) {
    if (*head1 == NULL) {     // X1 is empty
        *head1 = *head2;
        *tail1 = *tail2;
    } else if (*head2 != NULL) { // Both non-empty
        (*tail1)->next = *head2;
        (*head2)->prev = *tail1;
        *tail1 = *tail2;
    }
    // Make X2 empty, since its nodes now belong to X1
    *head2 = *tail2 = NULL;
}

// Main
int main() {
    struct Node *head1 = NULL, *tail1 = NULL;
    struct Node *head2 = NULL, *tail2 = NULL;

    int n1, n2, val;
    printf("Enter number of elements in List X1: ");
    scanf("%d", &n1);
    printf("Enter elements of X1: ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &val);
        insertRear(&head1, &tail1, val);
    }

    printf("Enter number of elements in List X2: ");
    scanf("%d", &n2);
    printf("Enter elements of X2: ");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &val);
        insertRear(&head2, &tail2, val);
    }

    printf("X1 before concatenation: ");
    traverseForward(head1);
    printf("X2 before concatenation: ");
    traverseForward(head2);

    concatenate(&head1, &tail1, &head2, &tail2);

    printf("\nAfter concatenation, X1 = ");
    traverseForward(head1);
    printf("X2 is now empty.\n");

    return 0;
}
