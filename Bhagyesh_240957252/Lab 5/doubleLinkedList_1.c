#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

// Function to create a new node
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

// Insert at rear (append)
void insertRear(int value) {
    struct Node* newNode = createNode(value);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Delete from rear
void deleteRear() {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = tail;
    if (head == tail) {
        head = tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = NULL;
    }
    free(temp);
}

// Insert at specific position (1-based indexing)
void insertAtPosition(int value, int pos) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    struct Node* newNode = createNode(value);

    if (pos == 1) { // Insert at head
        newNode->next = head;
        if (head != NULL)
            head->prev = newNode;
        head = newNode;
        if (tail == NULL) // list was empty
            tail = newNode;
        return;
    }

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = newNode;
    else
        tail = newNode; // Inserted at end
    temp->next = newNode;
    newNode->prev = temp;
}

// Delete from specific position
void deleteAtPosition(int pos) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    struct Node* temp = head;

    if (pos == 1) { // delete head
        if (head == tail) {
            head = tail = NULL;
        } else {
            head = head->next;
            head->prev = NULL;
        }
        free(temp);
        return;
    }

    for (int i = 1; i < pos && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }
    if (temp == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        temp->prev->next = temp->next;
        if (temp->next)
            temp->next->prev = temp->prev;
    }
    free(temp);
}

// Insert after a specific value
void insertAfterValue(int val, int newVal) {
    struct Node* temp = head;
    while (temp != NULL && temp->data != val) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Value %d not found!\n", val);
        return;
    }
    struct Node* newNode = createNode(newVal);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = newNode;
    else
        tail = newNode; // at end
    temp->next = newNode;
}

// Insert before a specific value
void insertBeforeValue(int val, int newVal) {
    struct Node* temp = head;
    while (temp != NULL && temp->data != val) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Value %d not found!\n", val);
        return;
    }
    struct Node* newNode = createNode(newVal);
    newNode->next = temp;
    newNode->prev = temp->prev;

    if (temp->prev != NULL)
        temp->prev->next = newNode;
    else
        head = newNode; // inserted before head
    temp->prev = newNode;
}

// Traverse forward
void traverseForward() {
    struct Node* temp = head;
    if (!temp) {
        printf("List is empty.\n");
        return;
    }
    printf("Forward traversal: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Traverse reverse
void traverseReverse() {
    struct Node* temp = tail;
    if (!temp) {
        printf("List is empty.\n");
        return;
    }
    printf("Reverse traversal: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// Menu
int main() {
    int choice, val, pos, target;
            printf("\n--- Doubly Linked List Menu ---\n");
        printf("1. Insert at rear\n2. Delete from rear\n3. Insert at position\n4. Delete at position\n");
        printf("5. Insert after value\n6. Insert before value\n7. Traverse forward\n8. Traverse reverse\n0. Exit\n");
    do {

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &val);
            insertRear(val);
            break;
        case 2:
            deleteRear();
            break;
        case 3:
            printf("Enter value and position: ");
            scanf("%d %d", &val, &pos);
            insertAtPosition(val, pos);
            break;
        case 4:
            printf("Enter position: ");
            scanf("%d", &pos);
            deleteAtPosition(pos);
            break;
        case 5:
            printf("Enter target value and new value: ");
            scanf("%d %d", &target, &val);
            insertAfterValue(target, val);
            break;
        case 6:
            printf("Enter target value and new value: ");
            scanf("%d %d", &target, &val);
            insertBeforeValue(target, val);
            break;
        case 7:
            traverseForward();
            break;
        case 8:
            traverseReverse();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

