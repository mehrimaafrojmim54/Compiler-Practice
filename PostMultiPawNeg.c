#include <stdio.h>
#include <ctype.h>
#include <math.h>

int stack[100];
int top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}

int evaluatePostfix(char* expr) {
    int i = 0;

    while (expr[i] != '\0') {

        // Skip space
        if (expr[i] == ' ') {
            i++;
            continue;
        }

        // Negative number handle
        if (expr[i] == '-' && isdigit(expr[i + 1])) {
            i++;  // skip '-'
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push(-num);
        }

        // Positive multi-digit number
        else if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push(num);
        }

        // Operator
        else {
            int val2 = pop();
            int val1 = pop();

            switch (expr[i]) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': push(val1 / val2); break;
                case '^': push(pow(val1, val2)); break;
            }
            i++;
        }
    }
    return pop();
}

int main() {
    char expr[] = "-12 3 * 2 ^";
    printf("Result: %d\n", evaluatePostfix(expr));
    return 0;
}
