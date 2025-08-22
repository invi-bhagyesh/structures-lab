#include <stdio.h>

#define MAX 100

struct Student {
    char name[50];
    int roll_no;
    float marks;
};

void read_students(struct Student *s, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", (s + i)->name);
        printf("Roll No: ");
        scanf("%d", &(s + i)->roll_no);
        printf("Marks: ");
        scanf("%f", &(s + i)->marks);
    }
}

void display_students(struct Student *s, int n) {
    printf("\n%-10s %-20s %-10s\n", "Roll No", "Name", "Marks");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-10.2f\n", (s + i)->roll_no, (s + i)->name, (s + i)->marks);
    }
}

void display_topper(struct Student *s, int n) {
    int top_index = 0;
    float highest = s->marks;

    for (int i = 1; i < n; i++) {
        if ((s + i)->marks > highest) {
            highest = (s + i)->marks;
            top_index = i;
        }
    }

    printf("\nStudent with Highest Marks:\n");
    printf("Name: %s\n", (s + top_index)->name);
    printf("Roll No: %d\n", (s + top_index)->roll_no);
    printf("Marks: %.2f\n", (s + top_index)->marks);
}

int main() {
    struct Student students[MAX];
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    read_students(students, n);
    display_students(students, n);
    display_topper(students, n);

    return 0;
}

