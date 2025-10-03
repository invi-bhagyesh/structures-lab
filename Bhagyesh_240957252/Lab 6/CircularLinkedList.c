#include <stdio.h>
#include <stdlib.h>

// Define node structure
struct Node {
    int data;
    struct Node* next;
};

// Global pointers to first and last nodes
struct Node *First = NULL, *Last = NULL;

// Function to insert at the end
void insertEnd(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (First == NULL) {
        // List is empty
        First = newNode;
        Last = newNode;
        newNode->next = First; // Circular link
    } else {
        Last->next = newNode;
        Last = newNode;
        Last->next = First; // Maintain circular link
    }
    printf("Inserted %d at the end.\n", value);
}

// Function to delete from the beginning
void deleteBeginning() {
    if (First == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    if (First == Last) {
        // Only one node
        printf("Deleted %d from beginning.\n", First->data);
        free(First);
        First = NULL;
        Last = NULL;
    } else {
        struct Node* temp = First;
        printf("Deleted %d from beginning.\n", temp->data);
        First = First->next;
        Last->next = First;
        free(temp);
    }
}

// Function to delete from the end
void deleteEnd() {
    if (First == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    if (First == Last) {
        // Only one node
        printf("Deleted %d from end.\n", Last->data);
        free(Last);
        First = NULL;
        Last = NULL;
    } else {
        struct Node* temp = First;
        // Traverse to second last node
        while (temp->next != Last) {
            temp = temp->next;
        }
        printf("Deleted %d from end.\n", Last->data);
        free(Last);
        Last = temp;
        Last->next = First;
    }
}

// Function to display the list
void displayList() {
    if (First == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = First;
    printf("List: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != First);
    printf("\n");
}

int main() {
    int choice, value;
        printf("\nMenu:\n");
        printf("1. Insert at end\n");
        printf("2. Delete from beginning\n");
        printf("3. Delete from end\n");
        printf("4. Display list\n");
        printf("5. Exit\n");
    while (1) {

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertEnd(value);
                displayList();
                break;
            case 2:
                deleteBeginning();
                displayList();
                break;
            case 3:
                deleteEnd();
                displayList();
                break;
            case 4:
                displayList();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}

