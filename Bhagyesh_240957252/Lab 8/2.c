#include <stdio.h>
#include <stdlib.h>
#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

int isFull() {
    return (front == 0 && rear == MAX - 1) || (front == rear + 1);
}

int isEmpty() {
    return front == -1;
}

void enqueue(int item) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1) front = 0;
    rear = (rear + 1) % MAX;
    queue[rear] = item;
}

int dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return -1;
    }
    int item = queue[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX;
    return item;
}

void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();
    printf("Dequeued: %d\n", dequeue());
    enqueue(50);
    display();
    return 0;
}

