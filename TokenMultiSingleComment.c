#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keyword[] = {"int", "if", "for", "while", "else", "return", "float"};
int keywordCount = 7;

int isKeyword(char *str) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(str, keyword[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '-' || ch == '+' || ch == '*' || ch == '/' ||
            ch == '%' || ch == '=' || ch == '<' || ch == '>' || ch == '!');
}

int main() {
    char str[200];
    int i = 0;

    printf("Provide the code: ");
    fgets(str, sizeof(str), stdin);

    while (str[i] != '\0') {

        // ignore spaces
        if (isspace(str[i])) {
            i++;
            continue;
        }

        // ignore single line comment //
        if (str[i] == '/' && str[i + 1] == '/') {
            while (str[i] != '\0' && str[i] != '\n')
                i++;
            continue;
        }

        // ignore multi line comment /* */
        if (str[i] == '/' && str[i + 1] == '*') {
            i += 2;
            while (str[i] != '\0' && !(str[i] == '*' && str[i + 1] == '/'))
                i++;
            i += 2;
            continue;
        }

        // keyword or identifier
        if (isalpha(str[i])) {
            char temp[50];
            int k = 0;

            while (isalnum(str[i])) {
                temp[k++] = str[i++];
            }
            temp[k] = '\0';

            if (isKeyword(temp))
                printf("<KEYWORD, %s>\n", temp);
            else
                printf("<IDENTIFIER, %s>\n", temp);
        }

        // number
        else if (isdigit(str[i])) {
            char temp[50];
            int k = 0;

            while (isdigit(str[i])) {
                temp[k++] = str[i++];
            }
            temp[k] = '\0';

            printf("<NUMBER, %s>\n", temp);
        }

        // operator
        else if (isOperator(str[i])) {

            // double operator (==, <=, >=, !=)
            if ((str[i] == '=' || str[i] == '<' || str[i] == '>' || str[i] == '!')
                && str[i + 1] == '=') {

                printf("<OPERATOR, %c%c>\n", str[i], str[i + 1]);
                i += 2;
            }
            else {
                printf("<OPERATOR, %c>\n", str[i]);
                i++;
            }
        }

        // punctuator
        else if (str[i] == '(' || str[i] == ')' ||
                 str[i] == '{' || str[i] == '}' ||
                 str[i] == ';' || str[i] == ',') {

            printf("<PUNCTUATOR, %c>\n", str[i]);
            i++;
        }

        // other symbols
        else {
            printf("<SYMBOL, %c>\n", str[i]);
            i++;
        }
    }

    return 0;
}
