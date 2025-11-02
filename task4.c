#include <stdio.h>

void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main() {

    int choice, maxSize;

    printf("Enter the size of the stack: ");
    scanf("%d", &maxSize);
    int stack[maxSize];
    int top = -1;

    do {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top, maxSize);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void push(int stack[], int *top, int maxSize) {

    int item;
    if (*top == maxSize - 1) {
        printf("Stack Overflow! Cannot push more elements\n");
        return;
    }

    printf("Enter the element to push: ");
    scanf("%d", &item);

    stack[++(*top)] = item;
    printf("%d pushed to stack\n", item);
}

void pop(int stack[], int *top) {

    if (*top == -1) {
        printf("Stack Underflow! Cannot pop from empty stack\n");
        return;
    }

    printf("%d popped from stack\n", stack[(*top)--]);
}

void peek(int stack[], int top) {

    if (top == -1) {
        printf("Stack is empty! Nothing to peek\n");
        return;
    }

    printf("Top element is: %d\n", stack[top]);
}

void display(int stack[], int top) {

    if (top == -1) {
        printf("Stack is empty!\n");
        return;
    }

    printf("Stack elements (top to bottom):\n");
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}
