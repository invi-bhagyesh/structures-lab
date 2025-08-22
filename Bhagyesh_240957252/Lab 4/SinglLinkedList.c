#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* createNode(int data);
void insertBefore(Node** head, int beforeData, int newData);
void insertAfter(Node* head, int afterData, int newData);
void deleteNode(Node** head, int key);
void traverse(Node* head);
void reverseList(Node** head);
void sortList(Node* head);
void deleteAlternateNodes(Node* head);
void sortedInsert(Node** head, int newData);

int main() {
    Node* head = NULL;
    int choice, data, key, beforeData, afterData;
        printf("\nMenu:\n");
        printf("1. Insert before an element\n");
        printf("2. Insert after an element\n");
        printf("3. Delete an element\n");
        printf("4. Traverse and display list\n");
        printf("5. Reverse the list\n");
        printf("6. Sort the list\n");
        printf("7. Delete every alternate node\n");
        printf("8. Insert into sorted list\n");
        printf("9. Exit\n");

    while(1) {

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter element before which to insert: ");
                scanf("%d", &beforeData);
                printf("Enter element to insert: ");
                scanf("%d", &data);
                insertBefore(&head, beforeData, data);
                break;
            case 2:
                printf("Enter element after which to insert: ");
                scanf("%d", &afterData);
                printf("Enter element to insert: ");
                scanf("%d", &data);
                insertAfter(head, afterData, data);
                break;
            case 3:
                printf("Enter element to delete: ");
                scanf("%d", &key);
                deleteNode(&head, key);
                break;
            case 4:
                printf("List elements: ");
                traverse(head);
                break;
            case 5:
                reverseList(&head);
                printf("List reversed.\n");
                break;
            case 6:
                sortList(head);
                printf("List sorted.\n");
                break;
            case 7:
                deleteAlternateNodes(head);
                printf("Alternate nodes deleted.\n");
                break;
            case 8:
                printf("Enter element to insert in sorted list: ");
                scanf("%d", &data);
                sortedInsert(&head, data);
                break;
            case 9:
                // Free all nodes before exiting
                while(head) {
                    Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                printf("Exiting.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertBefore(Node** head, int beforeData, int newData) {
    if(*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // If the head node contains beforeData, insert at front
    if((*head)->data == beforeData) {
        Node* newNode = createNode(newData);
        newNode->next = *head;
        *head = newNode;
        printf("%d inserted before %d.\n", newData, beforeData);
        return;
    }

    Node* curr = *head;
    while(curr->next && curr->next->data != beforeData) {
        curr = curr->next;
    }

    if(curr->next == NULL) {
        printf("Element %d not found in the list.\n", beforeData);
        return;
    }

    Node* newNode = createNode(newData);
    newNode->next = curr->next;
    curr->next = newNode;
    printf("%d inserted before %d.\n", newData, beforeData);
}

void insertAfter(Node* head, int afterData, int newData) {
    if(head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* curr = head;
    while(curr && curr->data != afterData) {
        curr = curr->next;
    }

    if(curr == NULL) {
        printf("Element %d not found in the list.\n", afterData);
        return;
    }

    Node* newNode = createNode(newData);
    newNode->next = curr->next;
    curr->next = newNode;
    printf("%d inserted after %d.\n", newData, afterData);
}

void deleteNode(Node** head, int key) {
    if(*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* curr = *head;
    Node* prev = NULL;

    // If head node holds the key to be deleted
    if(curr->data == key) {
        *head = curr->next;
        free(curr);
        printf("Element %d deleted.\n", key);
        return;
    }

    // Search for the key
    while(curr && curr->data != key) {
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL) {
        printf("Element %d not found in the list.\n", key);
        return;
    }

    prev->next = curr->next;
    free(curr);
    printf("Element %d deleted.\n", key);
}

void traverse(Node* head) {
    if(head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* curr = head;
    while(curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void reverseList(Node** head) {
    Node *prev = NULL, *curr = *head, *next = NULL;

    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void sortList(Node* head) {
    if(head == NULL) return;

    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while(ptr1->next != lptr) {
            if(ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while(swapped);
}

void deleteAlternateNodes(Node* head) {
    if(head == NULL) return;

    Node* curr = head;
    Node* nextNode;

    while(curr != NULL && curr->next != NULL) {
        nextNode = curr->next;
        curr->next = nextNode->next;
        free(nextNode);
        curr = curr->next;
    }
}

void sortedInsert(Node** head, int newData) {
    Node* newNode = createNode(newData);

    // Special case for the head end
    if(*head == NULL || (*head)->data >= newData) {
        newNode->next = *head;
        *head = newNode;
        printf("%d inserted into sorted list.\n", newData);
        return;
    }

    Node* curr = *head;
    while(curr->next != NULL && curr->next->data < newData) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    printf("%d inserted into sorted list.\n", newData);
}

