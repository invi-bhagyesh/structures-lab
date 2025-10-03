#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

struct Task {
    int id;
    char name[20];
};

struct Task queue[MAX];
int front = -1, rear = -1;

// Check if queue is full
int isFull() {
    return (rear + 1) % MAX == front;
}

// Check if queue is empty
int isEmpty() {
    return front == -1;
}

// Enqueue
void enqueue(struct Task job) {
    if (isFull()) {
        printf("Queue is full! Cannot add task.\n");
        return;
    }
    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % MAX;
    queue[rear] = job;
    printf("Enqueued Task ID %d (%s)\n", job.id, job.name);
}

// Dequeue
struct Task dequeue() {
    struct Task job = {-1, ""};
    if (isEmpty()) {
        printf("Queue is empty! No task to dequeue.\n");
        return job;
    }
    job = queue[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX;
    return job;
}

int main() {
    srand(time(0));
    int n = 5;
    for (int i = 0; i < n; i++) {
        struct Task job;
        job.id = i + 1;
        sprintf(job.name, "Doc%d", rand() % 100);
        enqueue(job);
    }

    printf("\nProcessing print jobs:\n");
    while (!isEmpty()) {
        struct Task job = dequeue();
        printf("Printing Task ID %d (%s)\n", job.id, job.name);
    }
    return 0;
}

