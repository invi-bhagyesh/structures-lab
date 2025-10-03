// array_stack.c

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

bool isPalindrome(char str[]) {
    char stack[MAX];
    int top = -1;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        stack[++top] = str[i];
    }

    for (int i = 0; i < len; i++) {
        if (str[i] != stack[top--])
            return false;
    }

    return true;
}

bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool isBalanced(char exp[]) {
    char stack[MAX];
    int top = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        char ch = exp[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            stack[++top] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1 || !isMatching(stack[top--], ch)) {
                return false;
            }
        }
    }

    return top == -1;
}

int main() {
    char str[MAX];
    char expr[MAX];

    printf("Enter a string to check palindrome: ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';  // remove newline

    if (isPalindrome(str))
        printf("\"%s\" is a palindrome.\n\n", str);
    else
        printf("\"%s\" is NOT a palindrome.\n\n", str);

    printf("Enter an expression to check parentheses matching: ");
    fgets(expr, MAX, stdin);
    expr[strcspn(expr, "\n")] = '\0';  // remove newline

    if (isBalanced(expr))
        printf("Parentheses in expression \"%s\" are Balanced.\n", expr);
    else
        printf("Parentheses in expression \"%s\" are NOT Balanced.\n", expr);

    return 0;
}
