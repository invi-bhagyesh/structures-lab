// linkedlist_stack.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* push(Node* top, char data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = top;
    return temp;
}

Node* pop(Node* top, char* popped) {
    if (top == NULL) {
        *popped = '\0';
        return NULL;
    }
    *popped = top->data;
    Node* temp = top;
    top = top->next;
    free(temp);
    return top;
}

char peek(Node* top) {
    return top ? top->data : '\0';
}

int isEmpty(Node* top) {
    return top == NULL;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    Node* stack = NULL;
    int i = 0, j = 0;
    char token, popped;

    while ((token = infix[i++]) != '\0') {
        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            stack = push(stack, token);
        } else if (token == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                stack = pop(stack, &popped);
                postfix[j++] = popped;
            }
            stack = pop(stack, &popped); // remove '('
        } else {
            while (!isEmpty(stack) && precedence(token) <= precedence(peek(stack))) {
                stack = pop(stack, &popped);
                postfix[j++] = popped;
            }
            stack = push(stack, token);
        }
    }

    while (!isEmpty(stack)) {
        stack = pop(stack, &popped);
        postfix[j++] = popped;
    }

    postfix[j] = '\0';
}

typedef struct IntNode {
    int data;
    struct IntNode* next;
} IntNode;

IntNode* pushInt(IntNode* top, int data) {
    IntNode* temp = (IntNode*)malloc(sizeof(IntNode));
    temp->data = data;
    temp->next = top;
    return temp;
}

IntNode* popInt(IntNode* top, int* value) {
    if (top == NULL) {
        *value = 0;
        return NULL;
    }
    *value = top->data;
    IntNode* temp = top;
    top = top->next;
    free(temp);
    return top;
}

int evaluatePostfix(char* postfix) {
    IntNode* stack = NULL;
    int i = 0;
    char token;
    int op1, op2;

    while ((token = postfix[i++]) != '\0') {
        if (isdigit(token)) {
            stack = pushInt(stack, token - '0');
        } else {
            stack = popInt(stack, &op2);
            stack = popInt(stack, &op1);
            switch (token) {
                case '+': stack = pushInt(stack, op1 + op2); break;
                case '-': stack = pushInt(stack, op1 - op2); break;
                case '*': stack = pushInt(stack, op1 * op2); break;
                case '/': stack = pushInt(stack, op1 / op2); break;
                default:
                    printf("Invalid operator: %c\n", token);
                    return 0;
            }
        }
    }

    int result;
    stack = popInt(stack, &result);
    return result;
}

int main() {
    char infix[100], postfix[100];

    printf("Enter an infix expression (single-character operands): ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n\n", postfix);

    printf("Enter a postfix expression (digits and operators + - * /): ");
    fgets(postfix, sizeof(postfix), stdin);
    postfix[strcspn(postfix, "\n")] = '\0';

    int result = evaluatePostfix(postfix);
    printf("Evaluated result: %d\n", result);

    return 0;
}
