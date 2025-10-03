#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

void enqueue(int item) {
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = item;
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("Enqueued: %d\n", item);
}

int dequeue() {
    if (front == NULL) {
        printf("Queue empty\n");
        return -1;
    }
    struct Node *temp = front;
    int val = temp->data;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
    return val;
}

void display() {
    struct Node *temp = front;
    printf("Queue: ");
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    printf("Dequeued: %d\n", dequeue());
    display();
    return 0;
}

