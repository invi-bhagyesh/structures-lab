
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert node in descending order by exponent in doubly linked list
void insertTerm(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);

    // If list is empty
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;

    // Insert at beginning if exp is greater than head's exp
    if (exp > temp->exp) {
        newNode->next = temp;
        temp->prev = newNode;
        *head = newNode;
        return;
    }

    // Traverse to find the right position
    while (temp->next != NULL && temp->next->exp > exp) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        // Insert at end
        temp->next = newNode;
        newNode->prev = temp;
    } else if (temp->next->exp == exp) {
        // If term with same exponent exists, add coefficients
        temp->next->coeff += coeff;
        free(newNode);
        if (temp->next->coeff == 0) {
            // If coefficient becomes 0, delete the node
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            if (toDelete->next)
                toDelete->next->prev = temp;
            free(toDelete);
        }
    } else {
        // Insert in middle
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
}

// Function to print polynomial
void printPoly(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        if (temp->coeff != 0) {
            if (temp != head && temp->coeff > 0)
                printf("+");

            if (temp->exp == 0)
                printf("%d", temp->coeff);
            else if (temp->exp == 1)
                printf("%dx", temp->coeff);
            else
                printf("%dx^%d", temp->coeff, temp->exp);
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials and return the head of result
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* p1 = poly1;
    Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) {
            insertTerm(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else if (p2->exp > p1->exp) {
            insertTerm(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        } else {
            // Equal exponents, add coefficients
            int sumCoeff = p1->coeff + p2->coeff;
            if (sumCoeff != 0)
                insertTerm(&result, sumCoeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    // Add remaining terms of poly1
    while (p1 != NULL) {
        insertTerm(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    // Add remaining terms of poly2
    while (p2 != NULL) {
        insertTerm(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Function to free the list memory
void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *poly1 = NULL, *poly2 = NULL, *sum = NULL;
    int n, coeff, exp;

    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n);
    printf("Enter terms (coefficient exponent) in descending order of exponent:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly1, coeff, exp);
    }

    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n);
    printf("Enter terms (coefficient exponent) in descending order of exponent:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }

    printf("\nFirst Polynomial: ");
    printPoly(poly1);

    printf("Second Polynomial: ");
    printPoly(poly2);

    sum = addPolynomials(poly1, poly2);
    printf("Sum Polynomial: ");
    printPoly(sum);

    // Free all lists
    freeList(poly1);
    freeList(poly2);
    freeList(sum);

    return 0;
}
