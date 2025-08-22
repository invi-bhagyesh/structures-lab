
#include <stdio.h>

#define MAX 100

struct student {
    char name[50];
    int roll_no;
    char grade;
};

void read_students(struct student s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", s[i].name);
        printf("Roll No: ");
        scanf("%d", &s[i].roll_no);
        printf("Grade: ");
        scanf(" %c", &s[i].grade);
    }
}

void display_students(struct student s[], int n) {
    printf("\n%-10s %-10s %-10s\n", "Roll No", "Name", "Grade");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-10s %-10c\n", s[i].roll_no, s[i].name, s[i].grade);
    }
}

void sort_students_by_roll(struct student s[], int n) {
    struct student temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j].roll_no > s[j + 1].roll_no) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct student students[MAX];
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    read_students(students, n);

    printf("\nStudent Information Before Sorting:\n");
    display_students(students, n);

    sort_students_by_roll(students, n);

    printf("\nStudent Information After Sorting by Roll Number:\n");
    display_students(students, n);

    return 0;
}
