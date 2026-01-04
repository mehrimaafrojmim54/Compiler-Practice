#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int stack[100];
int top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}

int evaluatePrefix(char* expr) {
    int length = strlen(expr);

    // Right to Left scan
    for (int i = length - 1; i >= 0; i--) {

        // Skip space
        if (expr[i] == ' ')
            continue;

        // Multi-digit number handle
        if (isdigit(expr[i])) {
            int num = 0;
            int power10 = 1;

            while (i >= 0 && isdigit(expr[i])) {
                num = num + (expr[i] - '0') * power10;
                power10 *= 10;
                i--;
            }
            i++;   // extra decrement adjust
            push(num);
        }
        else {
            int val1 = pop();
            int val2 = pop();

            switch (expr[i]) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': push(val1 / val2); break;
                case '^': push(pow(val1, val2)); break;
            }
        }
    }
    return pop();
}

int main() {
    // USER INPUT নেয় না
    char expr[] = "^ * + 12 3 2 3";

    printf("Result: %d\n", evaluatePrefix(expr));
    return 0;
}
