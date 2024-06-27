#include "stack.h"
#include <stdio.h>

 #define MAXVAL 100
static double val[MAXVAL];
static int sp;

void push(double x) {
    if (sp < MAXVAL) {
        val[sp++] = x;
    } else {
        printf("push: can't push %g\n", x);
    }
}


double pop(void) {
    if (sp > 0) {
        return val[--sp];
    }

    printf("pop: stack is empty\n");
    return 0.0;
}

