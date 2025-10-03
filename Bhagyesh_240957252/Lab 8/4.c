#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    char name[30];
    int age;
    int priority;
    struct Patient *next;
};

struct Patient *front = NULL, *rear = NULL;

void enqueue(char *name, int age, int priority) {
    struct Patient *newNode = (struct Patient*) malloc(sizeof(struct Patient));
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->priority = priority;
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("Added Patient: %s (Age %d, Priority %d)\n", name, age, priority);
}

struct Patient* dequeue() {
    if (front == NULL) {
        printf("No patients in queue.\n");
        return NULL;
    }
    struct Patient *temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    return temp;
}

void display() {
    struct Patient *temp = front;
    printf("Patients in queue:\n");
    while (temp) {
        printf("%s (Age %d, Priority %d)\n", temp->name, temp->age, temp->priority);
        temp = temp->next;
    }
}

int main() {
    enqueue("Alice", 30, 2);
    enqueue("Bob", 45, 1);
    enqueue("Charlie", 25, 3);

    display();

    struct Patient *p = dequeue();
    if (p) {
        printf("Dequeued Patient: %s (Age %d, Priority %d)\n", p->name, p->age, p->priority);
        free(p);
    }
    display();
    return 0;
}
