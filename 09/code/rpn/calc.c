#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "stack.h"

int main(void) {
    int type;
    double num;

    while ((type = gettoken(&num)) != EOF) {
        switch (type) {
            case NUMBER:
                push(num);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                num = pop();
                push(pop() - num);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                num = pop();
                if (num != 0.0) {
                    push(pop() / pop());
                } else {
                    printf("Zero division\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            case 'q':
                return 0;
            default:
                printf("unknown: %c\n", type);
        }
    }
    return 0;
}
